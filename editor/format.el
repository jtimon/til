;;; format.el --- batch reindent of til files using til-mode  -*- lexical-binding: t; -*-

;; Reindents every file named in `command-line-args-left' in place, applying
;; the same rules `til-mode' uses interactively.  Invoked by the merge script
;; (examples/merge_commit.til) as:
;;
;;   emacs -Q --batch -l editor/til-mode.el -l editor/format.el \
;;         -f til-format-batch $(git ls-files '*.til')
;;
;; `-Q --batch' is deliberate: -Q skips all init files (so this never starts
;; an Emacs server) and --batch runs headless and exits without connecting to
;; any running daemon via emacsclient.  Other Emacs servers or sessions are
;; therefore left completely untouched.

(require 'til-mode)
(require 'cl-lib)

(defun til-format-batch ()
  "Reindent each file in `command-line-args-left' in place with `til-mode'.
Only files whose content actually changes are rewritten."
  (let ((files command-line-args-left))
    (setq command-line-args-left nil)
    ;; Silence til-mode's indentation debug `message' calls so batch output
    ;; only reports the files that were reformatted.
    (cl-letf (((symbol-function 'message) (lambda (&rest _) nil)))
      (dolist (file files)
        (with-temp-buffer
          (insert-file-contents file)
          (let ((orig (buffer-string)))
            (til-mode)
            (indent-region (point-min) (point-max))
            (unless (string= orig (buffer-string))
              (write-region (point-min) (point-max) file nil 'quiet)
              (princ (format "formatted %s\n" file)))))))))

(provide 'format)
;;; format.el ends here
