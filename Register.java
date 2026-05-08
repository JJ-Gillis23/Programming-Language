import java.util.*;

public class Register {
    private String name;
    private String type;
    private Object value;
    HashMap<String, Float> vec = new HashMap<>();

    public Register(String name, String type) {
        this.name = name;
        this.type = type;
        switch(type) {
            case "float":
            case "bool":
                value = 0;
                break;
            case "string":
                value = "";
                break;
            case "vector3":
                vec.put("r", 0.0f);
                vec.put("g", 0.0f);
                vec.put("b", 0.0f);
                value = vec;
                break;
        }
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public Object getValue() {
        return value;
    }

    public void setValue(Object value) {
        this.value = value;
    }
    public void setVector(String component, Float value)
    {
        vec.put(component,value);
    }
    public Float getVector(String component)
    {
        return vec.get(component);
    }
}