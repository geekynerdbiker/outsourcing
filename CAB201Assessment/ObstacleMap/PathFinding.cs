using CAB201_Assignment.Obstacles.Nodes;
using Obstacles;

namespace CAB201_Assignment.ObstacleMap
{
    interface IPathfinding
    {
        List<List<Node>> GenerateMap();
    }

    public class PathFinding
    {
        NodeMap NodeMap;
        Bounds bounds;
        Node StartNode;
        Node EndNode;
        Node[,] Grid;
        int Rows
        {
            get { return Grid.GetLength(0) - 1; }
        }

        int Columns
        {
            get { return Grid.GetLength(1) - 1; }
        }

        public PathFinding(NodeMap nodeMap)
        {
            NodeMap = nodeMap;
            StartNode = new Node("Enter your current location (X,Y):", false).SetAsStart();
            EndNode = new Node("Enter the location of the mission objective (X,Y):", false).SetAsEnd();
            bounds = DynamicallyCreateBounds();
            Grid = nodeMap.GetNodeMatrix(bounds);
        }

        private Bounds DynamicallyCreateBounds()
        {
            Coordinate topLeftCoordinate = CreateTopLeft();
            Coordinate bottomRightCoordinate = CreateBottomRight();
            return new Bounds(topLeftCoordinate, bottomRightCoordinate);
        }

        private Coordinate CreateTopLeft()
        {
            Coordinate topLeft = new Coordinate(StartNode.X, StartNode.Y);
            foreach (Obstacle obstacle in NodeMap.GetObstacleList())
            {
                Bounds bounds = obstacle.GetBounds();
                if (bounds.TopLeftCoordinate.X < topLeft.X)
                {
                    topLeft.X = bounds.TopLeftCoordinate.X;
                }
                if (bounds.TopLeftCoordinate.Y < topLeft.Y)
                {
                    topLeft.Y = bounds.TopLeftCoordinate.Y;
                }
            }

            return topLeft;
        }

        private Coordinate CreateBottomRight()
        {
            Coordinate bottomRight = new Coordinate(EndNode.X, EndNode.Y);
            foreach (Obstacle obstacle in NodeMap.GetObstacleList())
            {
                Bounds bounds = obstacle.GetBounds();
                if (bounds.TopLeftCoordinate.X < bottomRight.X)
                {
                    bottomRight.X = bounds.TopLeftCoordinate.X;
                }
                if (bounds.TopLeftCoordinate.Y < bottomRight.Y)
                {
                    bottomRight.Y = bounds.TopLeftCoordinate.Y;
                }
            }

            return bottomRight;
        }

        public void FindSafePath()
        {
            Stack<Node> path = FindPath();
            foreach (Node node in path)
            {
                Console.WriteLine($"PathFinding: {node.X}, {node.Y}");
            }
        }

        private Stack<Node> FindPath()
        {
            Stack<Node> Path = new Stack<Node>();
            PriorityQueue<Node, float> OpenList = new PriorityQueue<Node, float>();
            List<Node> ClosedList = new List<Node>();
            List<Node> adjacencies;
            Node current = StartNode;

            OpenList.Enqueue(StartNode, StartNode.F);

            while (OpenList.Count != 0 && !ClosedList.Exists(x => x.Position == EndNode.Position))
            {
                current = OpenList.Dequeue();
                ClosedList.Add(current);
                adjacencies = GetAdjacentNodes(current);

                foreach (Node n in adjacencies)
                {
                    if (!ClosedList.Contains(n) && !n.Solid)
                    {
                        bool isFound = false;
                        foreach (var oLNode in OpenList.UnorderedItems)
                        {
                            if (oLNode.Element == n)
                            {
                                isFound = true;
                            }
                        }
                        if (!isFound)
                        {
                            n.Parent = current;
                            n.DistanceToTarget = Math.Abs(n.X - EndNode.X) + Math.Abs(n.Y - EndNode.Y);
                            n.Cost = n.Weight + n.Parent.Cost;
                            OpenList.Enqueue(n, n.F);
                        }
                    }
                }
            }

            // construct path, if end was not closed return null
            if (!ClosedList.Exists(x => x.Position == EndNode.Position))
            {
                return null;
            }

            // if all good, return path
            Node temp = ClosedList[ClosedList.IndexOf(current)];
            if (temp == null) return null;
            do
            {
                Path.Push(temp);
                temp = temp.Parent;
            } while (temp != StartNode && temp != null);

            return Path;
        }

        private List<Node> GetAdjacentNodes(Node node)
        {
            List<Node> AdjacentNodes = new List<Node>();

            int row = node.Y;
            int col = node.X;

            if (row + 1 < Rows)
            {
                AdjacentNodes.Add(Grid[col, row + 1]);
            }
            if (row - 1 >= 0)
            {
                AdjacentNodes.Add(Grid[col, row - 1]);
            }
            if (col - 1 >= 0)
            {
                AdjacentNodes.Add(Grid[col - 1, row]);
            }
            if (col + 1 < Columns)
            {
                AdjacentNodes.Add(Grid[col + 1, row]);
            }

            return AdjacentNodes;
        }
    }
}
