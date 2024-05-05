using CAB201_Assignment.ObstacleMap;
using CAB201_Assignment.Obstacles.Nodes;

namespace Obstacles;
public class Guard : Obstacle
{
    public new const bool IsIgnored = false;
    public new const char Marker = 'g';
    // in a perfect world and to save memory we want all instances of the class to implement the same factory instance
    public override Coordinate Origin { get; }
    
    public Guard() : base(Marker)
    {
        Origin = new Coordinate("Enter the guard's location (X,Y):");
    }

    public override bool HasVision(Coordinate coordinate)
    {
        /*Console.WriteLine($"{coordinate.Position[0]} == ${Origin.Position[1]} && ${coordinate.Position[0]} == ${Origin.Position[1]}");*/
        if (coordinate.Position[0] == Origin.Position[0] && coordinate.Position[1] == Origin.Position[1])
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
        return new Bounds(Origin, Origin);
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
        /*List<Node> nodes = new List<Node>();
        if (Origin.IsBetween(bounds))
        {
            Node origin = CreateNode(Origin);
            nodes.Add(origin);
        }
        return nodes;*/
    }
}