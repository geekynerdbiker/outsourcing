using CAB201_Assignment.Obstacles.Nodes;
using Obstacles;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Xml.Linq;
using Util;

/**
 * Responsible for printing out the map, nothing more than that.
 */
namespace CAB201_Assignment.ObstacleMap
{

    public class MarkerMap
    {
        private NodeMap NodeMap;
        private Bounds bounds;
        private char[,] _charMap;

        public MarkerMap(NodeMap nodeMap) 
        {
            NodeMap = nodeMap;

            Coordinate topLeftCoordinate = Input.PromptCoordinate("Enter the location of the top-left cell of the map (X,Y):");
            Coordinate bottomRightCoordinate = Input.PromptCoordinate("Enter the location of the bottom-right cell of the map (X,Y):");
            ValidateInputs(topLeftCoordinate , bottomRightCoordinate);

            bounds = new Bounds(topLeftCoordinate, bottomRightCoordinate);

            _charMap = InitalizeCharMap();
        }

        /// <summary>
        /// Validates the inputs given so that the bounds is not negative or unrealistic.
        /// </summary>
        /// <param name="parameter1">Description of the first parameter.</param>
        /// <param name="parameter2">Description of the second parameter.</param>
        /// <returns>Description of the return value (if applicable).</returns>
        /// <exception cref="ExceptionType">Description of exceptions thrown (if any).</exception>
        /// <remarks>You probably don't need this function, but since I thought we were dealing in the bounds of only positive integers I thought this was more than reasonable.</remarks>
        private static void ValidateInputs(Coordinate topLeftCoordinate, Coordinate bottomRightCoordinate)
        {
            if (topLeftCoordinate.X > bottomRightCoordinate.X && topLeftCoordinate.Y > bottomRightCoordinate.Y)
            {
                throw new Exception("Invalid Input");
            }
        }

        /// <summary>
        /// Display
        /// </summary>
        /// <param name="parameter1">Description of the first parameter.</param>
        /// <param name="parameter2">Description of the second parameter.</param>
        /// <returns>Description of the return value (if applicable).</returns>
        /// <exception cref="ExceptionType">Description of exceptions thrown (if any).</exception>
        /// <remarks>Additional details, notes, or usage instructions.</remarks>
        public void DisplayObstacleMap()
        {
            /*Console.WriteLine("DisplayObstacleMap");
            Console.WriteLine(bounds.Rows);
            Console.WriteLine(bounds.Columns);*/
            for (int row = 0; row <= bounds.Rows; row++)
            {
                for (int column = 0; column <= bounds.Columns; column++)
                {
                    string marker = Char.ToString(_charMap[column, row]);
                    if (marker == "\0")
                    {
                        Console.Write(".");
                    }
                    else
                    {
                        Console.Write($"{marker}");
                    }

                }
                Console.WriteLine();
            }
        }

        /// <summary>
        /// Uses the CreateEmptyCharMap Method to Initalize a character array with Obstacle Markers in them.
        /// </summary>
        /// <returns>A 2 dimensional character array that has markers in it.</returns>
        /// <remarks>Additional details, notes, or usage instructions.</remarks>
        private char[,] InitalizeCharMap()
        {
            char[,] markerMap = CreateEmptyCharMap();
            foreach (Node node in NodeMap.GetNodeList(bounds))
            {
                // needs to converted to relative
                markerMap[node.getRelativeX(bounds), node.getRelativeY(bounds)] = node.Marker;
            }

            return markerMap;
        }

        /// <summary>
        /// CreateEmptyCharMap create a blank 2 dimensional character array. It uses the bounds columns and rows to determine it's size.
        /// </summary>
        /// <returns>A blank 2 diemsnional array</returns>
        /// <remarks>The Method is not relative.</remarks>
        private char[,] CreateEmptyCharMap()
        {
            // Console.WriteLine($"CharMap Dimensions: {bounds.Columns}, {bounds.Rows}");
            return new char[bounds.Columns + 1, bounds.Rows + 1];
        }
    }
}
