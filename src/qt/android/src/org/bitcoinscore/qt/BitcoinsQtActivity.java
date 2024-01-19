package org.bitcoinscore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class BitcoinsQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File bitcoinsDir = new File(getFilesDir().getAbsolutePath() + "/.bitcoins");
        if (!bitcoinsDir.exists()) {
            bitcoinsDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
