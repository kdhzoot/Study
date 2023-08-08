class Hello {
    public static void main(String[] args) {
        Hi a = new Hi();
        a.setxy();
        Hi b = (Hi) a.clone();

        System.out.println(b);
    }
}

