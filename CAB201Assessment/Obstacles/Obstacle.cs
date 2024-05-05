using CAB201_Assignment.ObstacleMap;
using CAB201_Assignment.Obstacles.Nodes;
using System.Net;
using System.Runtime.CompilerServices;

namespace Obstacles
{
    [Serializable]
    public class ObstacleCreationException : Exception
    {
        public ObstacleCreationException() { }

        public ObstacleCreationException(string message)
            : base(message) { }

        public ObstacleCreationException(string message, Exception inner)
            : base(message, inner) { }
    }

    interface IObstacle
    {
        Coordinate Origin { get; }
        static char Marker { get; }
        static char Ignored { get; }
        int X { get; }
        int Y { get; }
        bool HasVision(Coordinate coordinate);
        Node GetNode(Coordinate coordinate);
        List<Node> GetNodes(Bounds bounds);
    }

    public abstract class Obstacle : NodeFactory, IObstacle
    {
        public abstract Coordinate Origin { get; }
        public static char Marker { get; }
        public bool IsIgnored;
        public int X { get => Origin.X; }
        public int Y { get => Origin.Y; }
        public Obstacle(char Marker) : base(Marker) { }

        /// <summary>
        /// Returns a node if the Obsticle has vision. Raises an Error if the Obsticle doesn't
        /// have vision. The coordinates are not relative to a grid selection but relative to 
        /// the whole grid. 
        /// 
        /// The implementation of this function can vary across different classes, but how
        /// the value is gotten doesn't matter too much.
        /// </summary>
        /// <param name="coordinate"></param>
        /// <returns></returns>
        public abstract bool HasVision(Coordinate coordinate);

        public Node GetNode(Coordinate coordinate)
        {
            if (HasVision(coordinate))
            {
                return CreateNode(coordinate);
            }
            else
            {
                throw new Exception();
            }
        }

        public char GetMarker()
        {
            return Marker;
        }

        public abstract Bounds GetBounds();
        public abstract List<Node> GetNodes(Bounds bounds);
    }
}