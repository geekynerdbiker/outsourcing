using CAB201_Assignment.Obstacles.Nodes;
using Obstacles;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics.CodeAnalysis;
using System.Dynamic;
using System.Net;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using Util;
using static CAB201_Assignment.ObstacleMap.MarkerMap;

namespace CAB201_Assignment.ObstacleMap
{
    interface INodeMap
    {
        void ShowSafeDirections();
        void DisplayObstacleMap();
        void FindSafePath();
        void AddObstacle(Obstacle obstacle);
        List<Obstacle> GetObstacleList();
        List<Node> GetNodeList(Bounds bounds);
    }

    public class NodeMap : INodeMap
    {
        private List<Obstacle> _obstacleList = new List<Obstacle>();

        public void AddObstacle(Obstacle obstacle)
        {
            _obstacleList.Add(obstacle);
        }

        public List<Obstacle> GetObstacleList()
        {
            return _obstacleList;
        }

        public void ShowSafeDirections()
        {
            Coordinate coordinates = new Coordinate("Enter your current location (X,Y):");
            if (ObstacleHasVisionOnNode(coordinates))
            {
                Console.WriteLine("Agent, your location is compromised. Abort mission.");
                return;
            }
            DisplayDirectionsAvailable(coordinates);
        }

        private void DisplayDirectionsAvailable(Coordinate coordinate)
        {
            string DirectionsAvailabe = GetDirectionsAvailable(coordinate);
            if (string.IsNullOrEmpty(DirectionsAvailabe))
            {
                Console.WriteLine("You cannot safely move in any direction. Abort mission.");
                return;
            }
            Console.WriteLine($"You can safely take any of the following directions: {DirectionsAvailabe}");
        }

        private string GetDirectionsAvailable(Coordinate coordinate)
        {
            StringBuilder directions = new StringBuilder();
            if (!ObstacleHasVisionOnNode(new Coordinate(coordinate.X, coordinate.Y - 1)))
            {
                directions.Append('N');
            }

            if (!ObstacleHasVisionOnNode(new Coordinate(coordinate.X, coordinate.Y + 1)))
            {
                directions.Append('S');
            }

            if (!ObstacleHasVisionOnNode(new Coordinate(coordinate.X + 1, coordinate.Y)))
            {
                directions.Append('E');
            }

            if (!ObstacleHasVisionOnNode(new Coordinate(coordinate.X - 1, coordinate.Y)))
            {
                
                directions.Append('W');
            }

            return directions.ToString();
        }

        private bool ObstacleHasVisionOnNode(Coordinate coordinate)
        {
            foreach (Obstacle obstacle in _obstacleList)
            {
                if (obstacle.HasVision(coordinate))
                {
                    return true;
                }
            }
            return false;
        }

        public void DisplayObstacleMap()
        {
            new MarkerMap(this).DisplayObstacleMap();
        }

        public void FindSafePath()
        {
            new PathFinding(this).FindSafePath();
        }

        public List<Node> GetNodeList(Bounds bounds)
        {
            List<Node> nodeList = new List<Node>();
            foreach (Obstacle obstacle in GetObstacleList())
            {
                List<Node> nodes = obstacle.GetNodes(bounds);
                foreach (Node node in nodes)
                {
                    // Console.WriteLine($"Array Bounds {node.X}, {node.Y}");
                    nodeList.Add(node);
                }
            }

            return nodeList;
        }

        public Node[,] GetNodeMatrix(Bounds bounds)
        {
            Console.WriteLine("Got Node Matrix");
            Node[,] nodeMatrix = new Node[bounds.Rows, bounds.Columns];
            List<Node> nodeList = GetNodeList(bounds);

            int X = 0;
            int Y = 0;

            while (X < nodeMatrix.GetLength(0) && Y < nodeMatrix.GetLength(1))
            {
                nodeMatrix[X, Y] = new Node(X, Y, false);

                X++;
                if (X >= nodeMatrix.GetLength(0))
                {
                    X = 0;
                    Y++;
                }
            }

            foreach(Node node in nodeList)
            {
                nodeMatrix[node.X, node.Y] = node;
            }

            return nodeMatrix;
        }
    }
}


