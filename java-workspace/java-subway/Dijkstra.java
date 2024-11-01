import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;
import java.util.PriorityQueue;

class Dijkstra {
    final static long MAX = 1000000;

    public static void path(LinkedList<Vertex> ll) {
        PriorityQueue<Vertex> pq = new PriorityQueue<>();

        for (Vertex v : ll) {
            v.dist = 0;
            pq.add(v);
        }

        while (!pq.isEmpty()) {
            Vertex u = pq.poll();

            for (Edge e : u.adj) {
                Vertex v = e.target;
                long w = e.weight;
                long distSum = u.dist + w;

                if (distSum < v.dist) {
                    pq.remove(v);
                    v.dist = distSum;
                    v.prev = u;
                    pq.add(v);
                }
            }
        }
    }

    public static void minTransfer(LinkedList<Vertex> ll) {
        PriorityQueue<Vertex> pq = new PriorityQueue<>();

        for (Vertex v : ll) {
            v.dist = 0;
            pq.add(v);
        }

        while (!pq.isEmpty()) {
            Vertex u = pq.poll();

            for (Edge e : u.adj) {
                Vertex v = e.target;
                long w = e.weight;

                if (e.isTransfer)
                    w += MAX;

                long distSum = u.dist + w;

                if (distSum < v.dist) {
                    pq.remove(v);
                    v.dist = distSum;
                    v.prev = u;
                    pq.add(v);
                }
            }
        }
    }

    public static void shortest(LinkedList<Vertex> ll) {
        List<Vertex> path = new ArrayList<>();
        Vertex target = ll.get(0);

        for (Vertex v : ll) {
            if (target.dist > v.dist)
                target = v;
        }

        for (Vertex v = target; v != null; v = v.prev)
            path.add(v);

        Collections.reverse(path);

        print(path);
        System.out.println(target.dist % MAX);
    }

    private static void print(List<Vertex> l) {
        for (int i = 0; i < l.size(); i++) {
            Vertex v = l.get(i);

            if (i != (l.size() - 1) &&
                    v.name.compareTo(l.get(i + 1).name) == 0) {
                System.out.print("[" + v.name + "]");
                i++;
            } else
                System.out.print(v.name);

            if (i != l.size() - 1)
                System.out.print(" ");
        }

        System.out.println();
    }
}