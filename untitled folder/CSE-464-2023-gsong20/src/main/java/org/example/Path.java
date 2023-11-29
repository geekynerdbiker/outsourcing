package org.example;

import java.util.List;

public class Path {
    private List<String> nodes;

    public Path(List<String> nodes) {
        this.nodes = nodes;
    }

    @Override
    public String toString() {
        return String.join(" -> ", nodes);
    }
}
