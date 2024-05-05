using System.Numerics;
using System.Xml.Schema;
using Util;

namespace CAB201_Assignment.Obstacles.Nodes
{
    interface ICoordinate
    {
        int X { get; }
        int Y { get; }
        public int[] Position { get; }
        public int GetAxis(char axis);
    }

    /// <summary>
    /// Coordinates is not a physical point on a map. Instead it is an imaginary point.
    /// </summary>
    public class Coordinate : IEquatable<Coordinate>
    {
        public int X { get; set; } // You need to be able to set these from outside of the class incase you want to change them, this can reduce arbitrary code creating the Axises in other parts of the program... take a look at NodeMap DynamicallyCreateBounds for example
        public int Y { get; set; }
        public virtual int[] Position { get => new int[] { X, Y }; }

        /// <summary>
        /// Node Constructor where the x and y coordinates are specified by the parameters.
        /// </summary>
        public Coordinate(int x, int y)
        {
            X = x;
            Y = y;
        }

        // For those inheriting from Coordinate
        protected Coordinate(Coordinate coordinate)
        {
            X = coordinate.X;
            Y = coordinate.Y;
        }

        /// <summary>
        /// Node Constructor where the x and y coordinates are specified by the user input.
        /// /// </summary>
        public Coordinate(string prompt)
        {
            int[] postion = Input.PromptCoordinateArray(prompt);

            X = postion[0];
            Y = postion[1];
        }

        public bool Equals(Coordinate? otherCoordinate)
        {
            if (otherCoordinate == null)
            {
                return false;
            }

            return (Position == otherCoordinate.Position);
        }

        public override bool Equals(Object? obj)
        {
            return this.Equals(obj as Coordinate);
        }

        public override int GetHashCode()
        {
            return this.GetHashCode();
        }

        public int GetAxis(char axis)
        {
            switch (axis)
            {
                case 'x':
                    return this.X;
                case 'y':
                    return this.Y;
                default:
                    throw new Exception("Axis not found.");
            }
        }

        public static int GetMinAxis(int axis1, int axis2)
        {
            return axis1 <= axis2 ? axis1 : axis2;
        }

        public static int GetMaxAxis(int axis1, int axis2)
        {
            return axis1 >= axis2 ? axis1 : axis2;
        }

        public bool IsBetween(Bounds bounds)
        {
            bool xIsValid = X > bounds.TopLeftCoordinate.X && X < bounds.BottomRightCoordinate.X;
            bool yIsValid = Y > bounds.TopLeftCoordinate.Y && Y < bounds.BottomRightCoordinate.Y;
            return (X > bounds.TopLeftCoordinate.X && X < bounds.BottomRightCoordinate.X);
        }

        public int getRelativeX(Bounds bounds)
        {
            return X - bounds.TopLeftCoordinate.X;
        }

        public int getRelativeY(Bounds bounds)
        {
            return Y - bounds.TopLeftCoordinate.Y;
        }
    }
}
