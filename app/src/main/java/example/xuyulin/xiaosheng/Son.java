package example.xuyulin.xiaosheng;

import android.util.Log;

/**
 * Create by 徐玉林.
 * Create on 2019-10-12.
 * Describe: =>
 */
public class Son extends Father {

    public Son(String name) {
        super(name);
        Log.e("xyl", "son初始化" + name);
    }

    @Override
    public String getName() {
        return "son获取名字" + this.name;
    }

    @Override
    public void start() {
        Log.e("xyl", "son start" + name);
    }
}
