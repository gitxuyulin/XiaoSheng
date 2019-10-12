package example.xuyulin.xiaosheng;

import android.util.Log;

/**
 * Create by 徐玉林.
 * Create on 2019-08-13.
 * Describe: =>
 */
public class NativeCallPresent {

    public NativeCallPresent() {
    }

    /**
     * native调类中的方法
     *
     * @param message
     * @param num
     */
    public void methodCommon(String message, int num) {
        Log.e("xyl", "普通方法-》信息：" + message + " 爱你" + num + "遍");
    }

    public static void methodStatic(String message, int num) {
        Log.e("xyl", "静态方法-》信息：" + message + " 爱你" + num + "遍");
    }

    public static native void callJavaCommonMethod();

    public static native void callJavaStaticMethod();

}
