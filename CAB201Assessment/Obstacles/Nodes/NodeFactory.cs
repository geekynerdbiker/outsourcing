using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

[Serializable]
public class MaxNodeLimitReached : Exception
{
    public MaxNodeLimitReached() { }

    public MaxNodeLimitReached(string message)
        : base(message) { }

    public MaxNodeLimitReached(string message, Exception inner)
        : base(message, inner) { }
}

namespace CAB201_Assignment.Obstacles.Nodes
{
    interface IVisionNodeFactory
    {
        Node CreateNode(Coordinate coordinate);
        Node CreateNode(int x, int y);
        Node CreateNode(string prompt);
    }

    /// <summary>
    /// Oftentimes when utilizing VisionNodes you want to create multiple instances
    /// of the class with the same Marker, this can become messy codewise. Therefore
    /// creating a Factory pattern should allow for less arbritary code.
    /// 
    /// VisionNodeFactories should be defined as a private field in the obsticle.
    /// </summary>
    public class NodeFactory : IVisionNodeFactory
    {
        /// <summary>
        /// Marker is the marker given to the Node and is what is shown on the map.
        /// </summary>
        private char Marker { get; }

        /// <summary>
        /// The VisionNodeFactory Constructor, used to define variables the marker that will be used when creating Nodes.
        /// </summary>
        /// <param name="marker">The marker to display on the map.</param>
        /// <usage>
        /// <code>
        /// VisionNodeFactory nodeFactory = new VisionNodeFactory('g') // g for guard
        /// nodeFactory.CreateVisionNode(7,7)
        /// nodeFactory.CreateVisionNode("Enter Object Position (x,y)")
        /// </code>
        /// </usage>
        public NodeFactory(char marker)
        {
            // Console.WriteLine($"NodeFactory: {marker}");
            Marker = marker;
        }

        public Node CreateNode(Coordinate coordinate)
        {
            return new Node(coordinate, true, Marker);
        }

        /// <summary>
        /// creates a new instance of a VisionNode with the Factory's defined marker.
        /// </summary>
        /// <param name="x">x coordinate of the VisionNode</param>
        /// <param name="y">y coordinate of the VisionNode</param>
        /// <returns>An instance of the VisionNode class with the specified parameters and marker</returns>
        public Node CreateNode(int x, int y)
        {
            return new Node(x, y, true, Marker);
        }

        /// <summary>
        /// creates a new instance of a VisionNode with the Factory's defined marker.
        /// </summary>
        /// <param name="prompt">The prompt used when creating the VisionNode</param>
        /// <returns>An instance of the VisionNode class with the specified parameters and marker</returns>f the VisionNode</param>
        public Node CreateNode(string prompt)
        {
            return new Node(prompt, true, Marker);
        }
    }
}
