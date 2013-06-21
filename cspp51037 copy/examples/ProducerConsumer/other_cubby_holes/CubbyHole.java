public class CubbyHole {
    private int contents;

    public synchronized int get() {
        return contents;
    }

    public synchronized void put(int value) {
        contents = value;
    }
}
