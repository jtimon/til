package org.til.androidsmoke;

import android.app.Activity;
import android.os.Bundle;
import android.system.Os;
import android.system.OsConstants;
import android.util.Log;
import java.io.PrintStream;

/** Runs the desktop JNI corpus inside an ordinary ART app process. */
public final class AndroidJniActivity extends Activity {
    @Override public void onCreate(Bundle state) {
        super.onCreate(state);
        new Thread(() -> {
            PrintStream saved = System.out;
            try (PrintStream actual = new PrintStream(openFileOutput("actual.txt", MODE_PRIVATE), false, "UTF-8")) {
                System.setOut(actual);
                Class.forName("JniLibTest").getMethod("main", String[].class)
                    .invoke(null, (Object) new String[0]);
                actual.flush();
                if (actual.checkError()) throw new AssertionError("could not write JNI corpus output");
                Log.i("TilAndroidSmoke", "JNI complete, page size: " + Os.sysconf(OsConstants._SC_PAGESIZE));
            } catch (ReflectiveOperationException | java.io.IOException error) {
                throw new AssertionError("JNI corpus failed", error);
            } finally {
                System.setOut(saved);
            }
        }, "til-jni-corpus").start();
    }
}
