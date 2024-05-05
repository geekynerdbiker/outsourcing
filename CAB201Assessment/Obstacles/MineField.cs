using CAB201_Assignment.Obstacles.Nodes;

/**
 * pattern
 * x.x
 * .x.
 * x.x
 */

namespace Obstacles
{
    /*public class MineField : Obstacle
    {
        public new const bool IsIgnored = false;
        public new const char Marker = 'b';
        // in a perfect world and to save memory we want all instances of the class to implement the same factory instance
        public override Coordinate Origin { get; }

        public MineField()
        {
            Origin = new Coordinate("Enter the MineField's location (X,Y):");
        }

        public override bool HasVision(Coordinate coordinate)
        {
            if (coordinate == Origin)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public override Bounds GetBounds()
        {
            if (IsIgnored)
            {
                throw new Exception("IsIgnored field set to true");
            }
            else
            {
                throw new NotImplementedException();
            }
        }
    }*/
}
