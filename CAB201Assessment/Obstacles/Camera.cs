using CAB201_Assignment.Obstacles.Nodes;
using Util;
using System.Data;
using System.Diagnostics.Metrics;
using System.Drawing;

namespace Obstacles;
public class Camera : Obstacle 
{
    public new const bool IsIgnored = true;
    public new const char Marker = 'c';
    // in a perfect world and to save memory we want all instances of the class to implement the same factory instance
    public override Coordinate Origin { get; }
    private char[] _directions = new char[4] { 'n', 'e', 's', 'w'};
    public char Direction { get; }

    public Camera() : base(Marker)
    {
        Origin = new Coordinate("Enter the Camera's location (X,Y):");
        Direction = PromptDirection("Enter the direction the camera is facing(n, s, e or w):");
    }

    private char PromptDirection(string prompt)
    {
        char input = Input.PromptChar(prompt);
        if (_directions.Contains(input))
        {
            return input;
        }
        throw new Exception();
    }

    public override bool HasVision(Coordinate coordinate)
    {
        double opposite;
        double adjacent;
        if (Direction == 'n' || Direction == 's')
        {
            opposite = GetRange(coordinate.X, Origin.X);
            adjacent = GetRange(coordinate.Y, Origin.Y);
        }
        else
        {
            opposite = GetRange(coordinate.Y, Origin.Y);
            adjacent = GetRange(coordinate.X, Origin.X);
        }


        double radians = double.IsNaN(Math.Atan(opposite / adjacent)) ? 0 : Math.Atan(opposite / adjacent);
        double degrees = radians * (180 / Math.PI);

        bool withinVision = degrees <= 45 && degrees >= -45;
        bool validOrientation = CheckOrientation(coordinate);

        return withinVision && validOrientation;
    }

    private bool CheckOrientation(Coordinate coordinate)
    {
        if ((Direction == 'n' && Origin.Y >= coordinate.Y) ||
            (Direction == 'e' && Origin.X <= coordinate.X) ||
            (Direction == 's' && Origin.Y <= coordinate.Y) ||
            (Direction == 'w' && Origin.X >= coordinate.X))
        {
            return true;
        }
        return false;
    }

    private int GetRange(int axis1, int axis2)
    {
        return Coordinate.GetMaxAxis(axis1, axis2) - Coordinate.GetMinAxis(axis1, axis2);
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

    public override List<Node> GetNodes(Bounds bounds)
    {
        // TODO: this is not the most effective way of getting the nodes that you need to build the map.
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
}