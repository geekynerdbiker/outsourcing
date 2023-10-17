//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.List;
//import java.util.Map;
//
//public class TrivialPursuit {
//
//    private static final int NUM_NODES = 40;
//    private static final int NUM_EXTRA_EDGES = 10;
//
//    private List<Node> nodes;
//    private Target target;
//    private List<Agent> agents;
//
//    public TrivialPursuit() {
//        nodes = new ArrayList<>();
//        for (int i = 0; i < NUM_NODES; i++) {
//            nodes.add(new Node(i, NUM_NODES));
//        }
//        connectNodes();
//        target = new Target(NUM_NODES);
//        agents = new ArrayList<>();
//    }
//
//    private void connectNodes() {
//        for (int i = 0; i < NUM_NODES; i++) {
//            for (int j = 0; j < NUM_NODES; j++) {
//                if (i != j) {
//                    nodes.get(i).addNeighbor(nodes.get(j));
//                }
//            }
//        }
//        for (int i = 0; i < NUM_EXTRA_EDGES; i++) {
//            int a = (int) (Math.random() * NUM_NODES);
//            int b = (int) (Math.random() * NUM_NODES);
//            while (a == b) {
//                b = (int) (Math.random() * NUM_NODES);
//            }
//            nodes.get(a).addNeighbor(nodes.get(b));
//            nodes.get(b).addNeighbor(nodes.get(a));
//        }
//    }
//
//    public void run() {
//        for (Agent agent : agents) {
//            agent.start(nodes);
//        }
//        while (target.isAlive()) {
//            for (Agent agent : agents) {
//                agent.takeAction(nodes);
//            }
//        }
//    }
//
//    public static void main(String[] args) {
//        TrivialPursuit game = new TrivialPursuit();
//        game.agents.add(new Agent0());
//        game.agents.add(new Agent1());
//        game.agents.add(new Agent2());
//        game.agents.add(new Agent3());
//        game.agents.add(new Agent4());
//        game.agents.add(new Agent5());
//        game.agents.add(new Agent6());
//        game.agents.add(new Agent7());
//        game.run();
//    }
//}
//
//class Node {
//
//    private int id;
//    public int NUM_NODES;
//    private List<Node> neighbors;
//
//    public Node(int id, int NUM_NODES) {
//        this.id = id;
//        this.NUM_NODES = NUM_NODES;
//        this.neighbors = new ArrayList<>();
//    }
//
//    public int getId() {
//        return id;
//    }
//    public void addNeighbor(Node neighbor) {
//        neighbors.add(neighbor);
//    }
//
//    public List<Node> getNeighbors() {
//        return neighbors;
//    }
//
//    public int isAdjacent(Node node) {
//        for (Node neighbor : neighbors) {
//            if (neighbor.getId() == node.getId()) {
//                return 1;
//            }
//        }
//        return 0;
//    }
//
//    public void kill() {
//        for (Node neighbor : neighbors) {
//            if (neighbor.isAdjacent(this) == 1) {
//                neighbor.kill();
//            }
//        }
//    }
//
//}
//
//class Target {
//
//    private int id;
//    private boolean alive;
//
//    public Target(int NUM_NODES) {
//        this.id = (int) (Math.random() * NUM_NODES);
//        this.alive = true;
//    }
//
//    public int getId() {
//        return id;
//    }
//
//    public boolean isAlive() {
//        return alive;
//    }
//
//    public void kill() {
//        this.alive = false;
//    }
//}
//
//abstract class Agent {
//
//    protected Node currentNode;
//
//    public void start(List<Node> nodes) {
//        currentNode = nodes.get(0);
//    }
//
//    public abstract void takeAction(List<Node> nodes);
//}
//
//class Agent0 extends Agent {
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        // Do nothing
//    }
//}
//
//class Agent1 extends Agent {
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = nodes.get(0);
//        for (Node neighbor : currentNode.getNeighbors()) {
//            if (neighbor.getId() < nextNode.getId()) {
//                nextNode = neighbor;
//            }
//        }
//        currentNode = nextNode;
//    }
//}
//
//class Agent2 extends Agent {
//
//    private Map<Node, Integer> distances;
//
//    @Override
//    public void start(List<Node> nodes) {
//        super.start(nodes);
//        distances = new HashMap<>();
//        for (Node node : nodes) {
//            distances.put(node, Integer.MAX_VALUE);
//        }
//        distances.put(currentNode, 0);
//    }
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = null;
//        int minDistance = Integer.MAX_VALUE;
//        for (Node node : currentNode.getNeighbors()) {
//            int distance = distances.get(node) + 1;
//            if (distance < minDistance) {
//                minDistance = distance;
//                nextNode = node;
//            }
//        }
//        currentNode = nextNode;
//        distances.put(currentNode, minDistance);
//    }
//}
//
//class Agent3 extends Agent {
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        // Do nothing
//    }
//}
//
//class Agent4 extends Agent {
//
//    private Map<Node, Double> probabilities;
//
//    @Override
//    public void start(List<Node> nodes) {
//        super.start(nodes);
//        probabilities = new HashMap<>();
//        for (Node node : nodes) {
//            probabilities.put(node, 1.0 / node.NUM_NODES);
//        }
//    }
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = null;
//        double maxProbability = 0.0;
//        for (Node node : currentNode.getNeighbors()) {
//            double probability = probabilities.get(node);
//            if (probability > maxProbability) {
//                maxProbability = probability;
//                nextNode = node;
//            }
//        }
//        currentNode = nextNode;
//        probabilities.put(currentNode, probabilities.get(currentNode) * 0.9);
//    }
//}
//
//class Agent5 extends Agent {
//
//    private Map<Node, Double> probabilities;
//    private Node target;
//
//    @Override
//    public void start(List<Node> nodes) {
//        super.start(nodes);
//        probabilities = new HashMap<>();
//        for (Node node : nodes) {
//            probabilities.put(node, 1.0 / node.NUM_NODES);
//        }
//        target = nodes.get(target.getId());
//    }
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = null;
//        double maxProbability = 0.0;
//        for (Node node : currentNode.getNeighbors()) {
//            double probability = probabilities.get(node) * (1.0 - target.isAdjacent(node));
//            if (probability > maxProbability) {
//                maxProbability = probability;
//                nextNode = node;
//            }
//        }
//        currentNode = nextNode;
//        probabilities.put(currentNode, probabilities.get(currentNode) * 0.9);
//    }
//}
//
//class Agent6 extends Agent {
//
//    private Map<Node, Double> probabilities;
//    private Node target;
//
//    @Override
//    public void start(List<Node> nodes) {
//        super.start(nodes);
//        probabilities = new HashMap<>();
//        for (Node node : nodes) {
//            probabilities.put(node, 1.0 / node.NUM_NODES);
//        }
//        target = nodes.get(target.getId());
//    }
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = null;
//        double maxProbability = 0.0;
//        for (Node node : currentNode.getNeighbors()) {
//            double probability = probabilities.get(node) * (1.0 - target.isAdjacent(node));
//            if (probability > maxProbability) {
//                maxProbability = probability;
//                nextNode = node;
//            }
//        }
//        currentNode = nextNode;
//        probabilities.put(currentNode, probabilities.get(currentNode) * 0.9);
//        if (target.isAdjacent(currentNode) == 1) {
//            target.kill();
//        }
//    }
//}
//
//class Agent7 extends Agent {
//
//    private Map<Node, Double> probabilities;
//    private Node target;
//
//    @Override
//    public void start(List<Node> nodes) {
//        super.start(nodes);
//        probabilities = new HashMap<>();
//        for (Node node : nodes) {
//            probabilities.put(node, 1.0 / node.NUM_NODES);
//        }
//        target = nodes.get(target.getId());
//    }
//
//    @Override
//    public void takeAction(List<Node> nodes) {
//        Node nextNode = null;
//        double maxProbability = 0.0;
//        for (Node node : currentNode.getNeighbors()) {
//            double probability = probabilities.get(node) * (1.0 - target.isAdjacent(node));
//            if (probability > maxProbability) {
//                maxProbability = probability;
//                nextNode = node;
//            }
//        }
//        currentNode = nextNode;
//        probabilities.put(currentNode, probabilities.get(currentNode) * 0.9);
//        if (target.isAdjacent(currentNode) == 1) {
//            target.kill();
//        } else {
//            Node[] neighbors = currentNode.getNeighbors().toArray(new Node[0]);
//            for (Node neighbor : neighbors) {
//                if (probabilities.get(neighbor) < 0.1) {
//                    probabilities.put(neighbor, 1.0 / neighbor.NUM_NODES);
//                }
//            }
//        }
//    }
//}