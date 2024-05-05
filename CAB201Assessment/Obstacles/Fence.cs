using CAB201_Assignment.ObstacleMap;
using CAB201_Assignment.Obstacles.Nodes;
using System.Diagnostics.Metrics;
using System;
using System.Dynamic;
using System.Text;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Obstacles;
public class Fence : Obstacle {
    public new const bool IsIgnored = false;

    public new const char Marker = 'f';
    public override Coordinate Origin { get; }
    public Coordinate End { get; }
    private char DifferingAxis
    {
        get
        {
            return GetDifferingAxis();
        }
    }
    private char CommonAxis 
    {
        get
        {
            return GetCommonAxis();
        }
    }

    public Fence() : base(Marker)
    {
        Origin = new Coordinate("Enter the location where the fence starts(X, Y):");
        End = new Coordinate("Enter the location where the fence ends (X,Y):");
        ValidateObstacleOrientation();
        GetNodes(new Bounds(new Coordinate(0,0), new Coordinate(7, 7)));
    }

    private bool ValidateObstacleOrientation()
    {
        if (Origin.X == End.X || Origin.Y == End.Y)
        {
            return true;
        }
        else
        {
            throw new ObstacleCreationException();
        }
    }

    public override bool HasVision(Coordinate coordinate)
    {
        switch (DifferingAxis)
        {
            case 'x':
                // Console.WriteLine($"X {coordinate.X} {coordinate.Y}, {GetMinAxis('x')},{GetMaxAxis('x')} {coordinate.Y == Origin.GetAxis(GetCommonAxis())}");
                return IsBetweenRange(coordinate.X, GetMinAxis('x'), GetMaxAxis('x')) && coordinate.Y == Origin.GetAxis(GetCommonAxis());
            case 'y':
                // Console.WriteLine($"Y {coordinate.Y} {coordinate.Y}, {GetMinAxis('y')},{GetMaxAxis('y')} {coordinate.X == Origin.GetAxis(GetCommonAxis())}");
                return IsBetweenRange(coordinate.Y, GetMinAxis('y'), GetMaxAxis('y')) && coordinate.X == Origin.GetAxis(GetCommonAxis());
            default:
                throw new Exception();
        }
    }

    private static bool IsBetweenRange(int value, int min, int max)
    {
        return value >= min && value <= max;
    }

    public override Bounds GetBounds()
    {
        return new Bounds(Origin, End);
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
        char differingAxis = GetDifferingAxis();

        int differingOrigin = Origin.GetAxis(differingAxis);
        int differingEnd = End.GetAxis(differingAxis);

        int minAxis = Coordinate.GetMinAxis(differingOrigin, differingEnd);
        // Console.WriteLine(minAxis);
        int maxAxis = Coordinate.GetMaxAxis(differingOrigin, differingEnd);

        for (int range = minAxis; range <= maxAxis; range++)
        {
            Coordinate coordinate;
            
            switch (differingAxis)
            {
                case 'x':
                    coordinate = new Coordinate(range, Origin.Y);
                    Console.WriteLine($"{coordinate.X}, {coordinate.Y}");
                    if (coordinate.IsBetween(bounds)) { nodes.Add(CreateNode(coordinate)); }
                    break;
                case 'y':
                    coordinate = new Coordinate(Origin.X, range);
                    if (coordinate.IsBetween(bounds)) { nodes.Add(CreateNode(coordinate)); }
                    break;
                default:
                    throw new Exception();    
            }
        }
        return nodes;*/
    }

    private int GetMinAxis(char axis)
    {
        return Origin.GetAxis(axis) < End.GetAxis(axis) ? Origin.GetAxis(axis) : End.GetAxis(axis);
    }

    private int GetMaxAxis(char axis)
    {
        return Origin.GetAxis(axis) > End.GetAxis(axis) ? Origin.GetAxis(axis) : End.GetAxis(axis);
    }

    private char GetDifferingAxis()
    {
        return Origin.X != End.X ? 'x' : 'y';
    }

    private char GetCommonAxis()
    {
        return Origin.X == End.X ? 'x' : 'y';
    }
}