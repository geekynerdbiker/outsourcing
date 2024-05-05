using CAB201_Assignment.Obstacles.Nodes;
using Util;

namespace Obstacles;

public class Sensor : Obstacle
{
    public new const bool IsIgnored = false;
    public new const char Marker = 's';
    // in a perfect world and to save memory we want all instances of the class to implement the same factory instance
    public override Coordinate Origin { get; }
    public double Range { get; }

    public Sensor() : base(Marker)
    {
        Origin = new Coordinate("Enter the sensor's location (X,Y):");
        Range = Input.PromptDouble("Enter the sensor's range (in klicks):");
    }

    public override bool HasVision(Coordinate coordinate)
    {
        double position = Math.Sqrt(Math.Pow(coordinate.X - Origin.X, 2) + Math.Pow(coordinate.Y - Origin.Y, 2));
        if ( Range >  position )
        {
            return true;
        }
        return false;
    }

    public override List<Node> GetNodes(Bounds bounds) 
    {
        List<Node> nodes = new List<Node>();
        for (int X = bounds.TopLeftCoordinate.X; X >= bounds.TopLeftCoordinate.X && X <= bounds.BottomRightCoordinate.X; X++)
        {
            for (int Y = bounds.TopLeftCoordinate.Y; Y >= bounds.TopLeftCoordinate.Y && Y <= bounds.BottomRightCoordinate.Y; Y++)
            {
                Coordinate coordinate = new Coordinate(X, Y);
                if (HasVision(coordinate))
                {
                    Node node = CreateNode(coordinate);
                    nodes.Add(node);
                }
            }
        }
        return nodes;
    }
    public override Bounds GetBounds()
    {
        Coordinate topLeft = new Coordinate(Origin.X - (int)Math.Ceiling(Range), Origin.Y - (int)Math.Ceiling(Range));
        Coordinate bottomRight = new Coordinate(Origin.X + (int)Math.Ceiling(Range), Origin.Y + (int)Math.Ceiling(Range));
        return new Bounds(topLeft, bottomRight);
    }
}