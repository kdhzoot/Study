public class Hi implements Cloneable {
    public int x = 1, y = 2;

    public void setxy(){
        this.x = 10;
        this.y = 20;
    }

    public String toString(){
        return "" + x + y;
    }
    public Object clone() {
        try {
            return super.clone();
        } catch (CloneNotSupportedException e) {

        }
        return null;
    }
}
