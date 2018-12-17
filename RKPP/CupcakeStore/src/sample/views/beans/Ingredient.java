package sample.views.beans;

public class Ingredient {
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getCalories() {
        return calories;
    }

    public void setCalories(float calories) {
        this.calories = calories;
    }

    private String name = "";
    private float calories = 0.0f;


    public Ingredient() {}
    public Ingredient(String name, float calories) {
        this.name = name;
        this.calories = calories;
    }
}
