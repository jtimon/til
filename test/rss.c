#include <linux/sched.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

// link_c force-includes the generated header before this file, so feature
// macros here cannot expose glibc's GNU-only clone declaration in sched.h.
extern int clone(int (*fn)(void *), void *stack, int flags, void *arg, ...);

typedef struct {
    int ready[2];
    int stop[2];
} RssWorker;

static void rss_fail(const char *what) {
    perror(what);
    exit(1);
}

static int rss_worker(void *arg) {
    RssWorker *worker = arg;
    close(worker->ready[0]);
    close(worker->stop[1]);
    char token = 1;
    if (write(worker->ready[1], &token, 1) != 1) _exit(1);
    if (read(worker->stop[0], &token, 1) != 1) _exit(1);
    _exit(0);
}

static void rss_case(int share_vm) {
    RssWorker worker;
    if (pipe(worker.ready) || pipe(worker.stop)) rss_fail("pipe");
    size_t stack_size = 1024 * 1024;
    char *stack = mmap(NULL, stack_size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (stack == MAP_FAILED) rss_fail("mmap stack");
    int flags = SIGCHLD | (share_vm ? CLONE_VM : 0);
    pid_t child = clone(rss_worker, stack + stack_size, flags, &worker);
    if (child < 0) rss_fail("clone");
    close(worker.ready[1]);
    close(worker.stop[0]);
    char token;
    if (read(worker.ready[0], &token, 1) != 1) rss_fail("worker ready");

    uint64_t tree_rss = current_rss_bytes(getpid());
    uint64_t child_rss = current_rss_bytes(child);
    // tree_rss already includes descendants; measure our own RSS directly
    // through a second sample after the worker has exited below.
    if (write(worker.stop[1], &token, 1) != 1) rss_fail("worker stop");
    int status;
    if (waitpid(child, &status, 0) != child) rss_fail("waitpid");
    close(worker.ready[0]);
    close(worker.stop[1]);
    if (munmap(stack, stack_size) != 0) rss_fail("munmap stack");
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "RSS worker failed\n");
        exit(1);
    }
    uint64_t own_rss = current_rss_bytes(getpid());
    uint64_t expected = own_rss + (share_vm ? 0 : child_rss);
    uint64_t difference = tree_rss > expected ? tree_rss - expected : expected - tree_rss;
    if (child_rss < 64 * 1024 * 1024 || difference > 8 * 1024 * 1024) {
        fprintf(stderr, "RSS share_vm=%d: tree=%llu own=%llu child=%llu expected=%llu\n",
                share_vm, (unsigned long long)tree_rss, (unsigned long long)own_rss,
                (unsigned long long)child_rss, (unsigned long long)expected);
        exit(1);
    }
}

void rss_regression(void) {
    // A large resident mapping makes double counting unambiguous. Keep both
    // workers alive with pipes rather than hoping to sample a brief vfork.
    size_t size = 64 * 1024 * 1024;
    void *resident = mmap(NULL, size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (resident == MAP_FAILED) rss_fail("mmap resident");
    memset(resident, 1, size);
    rss_case(1); // A distinct process leader sharing our address space.
    rss_case(0); // A fork-like child with its OWN address space must still count.
    if (munmap(resident, size) != 0) rss_fail("munmap resident");
}
