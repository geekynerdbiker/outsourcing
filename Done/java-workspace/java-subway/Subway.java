import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.LinkedList;

public class Subway {
    private static final HashMap<String, LinkedList<Vertex>> stations = new HashMap<>();
    private static final HashMap<String, Vertex> IDs = new HashMap<>();

    private static void getInput(String inputFile) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
            String nextLine;

            while ((nextLine = br.readLine()) != null) {
                if (nextLine.isEmpty())
                    break;

                String[] info = nextLine.split(" ");
                String id = info[0],name = info[1], line = info[2];

                Vertex v = new Vertex(id, name, line);
                LinkedList<Vertex> ll;

                if (stations.containsKey(name)) {
                    ll = stations.get(name);
                    for (Vertex target : ll) {
                        Edge e1 = new Edge(v, 5, true);
                        target.addEdge(e1);
                        Edge e2 = new Edge(target, 5, true);
                        v.addEdge(e2);
                    }
                } else
                    ll = new LinkedList<>();

                ll.add(v);
                stations.put(name, ll);
                IDs.put(id, v);

            }

            while ((nextLine = br.readLine()) != null) {
                String[] interval = nextLine.split(" ");
                String start = interval[0],dest = interval[1];

                long w = Long.parseLong(interval[2]);
                Vertex vs = IDs.get(start),vd = IDs.get(dest);

                Edge intervalEdge = new Edge(vd, w, false);
                vs.addEdge(intervalEdge);
            }

            br.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void command(String input) {
        String[] commands = input.split(" ");
        String start = commands[0], dest = commands[1];

        LinkedList<Vertex> lls = stations.get(start), lld = stations.get(dest);

        switch (commands.length) {
            case 2:
                Dijkstra.path(lls);
                Dijkstra.shortest(lld);
                break;
            case 3:
                if (commands[2].compareTo("!") == 0) {
                    Dijkstra.minTransfer(lls);
                    Dijkstra.shortest(lld);
                }
                break;
            default:
                break;
        }

        init();
    }

    private static void init() {
        for (Vertex v : IDs.values()) {
            v.dist = Long.MAX_VALUE;
            v.prev = null;
        }
    }

    public static void main(String[] args) {
        String dataFile = args[0];
        getInput(dataFile);

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("QUIT") == 0)
                    break;

                command(input);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}


