using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CAB201_Assignment.Obstacles.Nodes
{
    public class Bounds
    {
        public Coordinate TopLeftCoordinate { get; }
        public Coordinate BottomRightCoordinate { get; }
        public int Rows
        {
            get
            {
                return BottomRightCoordinate.Y - TopLeftCoordinate.Y;
            }
        }

        public int Columns
        {
            get
            {
                return BottomRightCoordinate.X - TopLeftCoordinate.X;
            }
        }
        public Bounds(Coordinate topLeftCoordinate, Coordinate bottomRightCoordinate)
        {
            this.TopLeftCoordinate = topLeftCoordinate;
            this.BottomRightCoordinate = bottomRightCoordinate;
        }
    }
}
