package example.xuyulin.xiaosheng;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.google.gson.Gson;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView sampleText;
    private TextView sampleCall;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("xiaosheng-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sampleText = findViewById(R.id.sample_text);
        sampleCall = findViewById(R.id.sample_call);
        sampleText.setOnClickListener(this);
        sampleCall.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.sample_text:
                int[] array = {1, 2, 3, 4, 5, 6};
                sampleText.setText("数组累加等于：" + getArraySum(array));
                int[][] objectArray = getObjectArray(3);
                Log.e("xyl", "数组" + new Gson().toJson(objectArray));
                break;
            case R.id.sample_call:
//                NativeCallPresent.callJavaStaticMethod();
//                NativeCallPresent.callJavaCommonMethod();
//                setAccessObject();
                setSuperInstace();
                break;
        }
    }

    /**
     * 可以native修改类中参数的字断
     */
    public void setAccessObject() {
        UserBean userBean = new UserBean();
        userBean.setAge(10);
        userBean.setName("王者");
        userBean.setSex("男");
//        accessInstaceField(userBean);
        accessStaticField(userBean);
        Log.e("xyl", "数据" + userBean.getSex());
    }

    /**
     * natice创建super的实例
     */
    public void setSuperInstace() {
        callSuperInstaceMethod();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String name);

    public native String getName(String name);

    public native String getCritical(String name);

    public native String getRegion(String name);

    public native int getArraySum(int[] array);

    public native int[][] getObjectArray(int size);

    public native static void accessInstaceField(UserBean userBean);

    public native void accessStaticField(UserBean userBean);

    public native static void callSuperInstaceMethod();
}
