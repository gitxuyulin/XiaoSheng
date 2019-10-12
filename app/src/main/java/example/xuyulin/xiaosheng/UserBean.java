package example.xuyulin.xiaosheng;

/**
 * Create by 徐玉林.
 * Create on 2019-10-10.
 * Describe: =>
 */
public class UserBean {
    private String name;
    private int age;
    private static String sex;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        UserBean.sex = sex;
    }
}
