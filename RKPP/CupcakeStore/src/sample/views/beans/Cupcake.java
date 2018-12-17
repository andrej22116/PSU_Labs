package sample.views.beans;

public class Cupcake {
    private String name = "";
    private float cost = 0;
    private float calories = 0;
    private String stuffing = "";
    private String dimensions = "";
    private String pastry = "";
    private String topping = "";

    public Cupcake() {
    }

    public Cupcake(String name, float cost, float calories, String stuffing, String dimensions, String pastry, String topping) {
        this.name = name;
        this.cost = cost;
        this.calories = calories;
        this.stuffing = stuffing;
        this.dimensions = dimensions;
        this.pastry = pastry;
        this.topping = topping;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getCost() {
        return cost;
    }

    public void setCost(float cost) {
        this.cost = cost;
    }

    public float getCalories() {
        return calories;
    }

    public void setCalories(float calories) {
        this.calories = calories;
    }

    public String getStuffing() {
        return stuffing;
    }

    public void setStuffing(String stuffing) {
        this.stuffing = stuffing;
    }

    public String getDimensions() {
        return dimensions;
    }

    public void setDimensions(String dimensions) {
        this.dimensions = dimensions;
    }

    public String getPastry() {
        return pastry;
    }

    public void setPastry(String pastry) {
        this.pastry = pastry;
    }

    public String getTopping() {
        return topping;
    }

    public void setTopping(String topping) {
        this.topping = topping;
    }
}
