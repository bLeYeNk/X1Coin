package org.x1coincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class X1coinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File x1coinDir = new File(getFilesDir().getAbsolutePath() + "/.x1coin");
        if (!x1coinDir.exists()) {
            x1coinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
