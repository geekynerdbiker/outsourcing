using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace Assignment.Obstacles.Nodes
{
    public class Node : Coordinate
    {
        public Node? Parent { get; set; }
        public char Marker { get; set; }
        public float DistanceToTarget { get; set; }
        public float Weight { get; set; }
        public float Cost { get; set; }
        public bool Start = false;
        public bool End = false;
        public bool Solid;
        public bool Open;
        public bool Closed;

        public float F
        {
            get
            {
                if (DistanceToTarget != -1 && Cost != -1)
                    return DistanceToTarget + Cost;
                else
                    return -1;
            }
        }
        
        public Node(Coordinate position, bool solid, char marker='.', float weight = 1) : base(position)
        {
            Parent = null;
            DistanceToTarget = -1;
            Cost = 1;
            Weight = weight;
            Solid = solid;
            Marker = marker;
        }

        public Node(string prompt, bool solid, char marker = '.', float weight = 1) : base(prompt)
        {
            Parent = null;
            DistanceToTarget = -1;
            Cost = 1;
            Weight = weight;
            Solid = solid;
            Marker = marker;
        }

        public Node(int x, int y, bool solid, char marker = '.', float weight = 1) : base(x, y)
        {
            Parent = null;
            DistanceToTarget = -1;
            Cost = 1;
            Weight = weight;
            Solid = solid;
            Marker = marker;
        }

        public void SetAsClosed()
        {
            Closed = true;
        }

        public void SetAsOpen()
        {
            Open = true;
        }

        public Node SetAsStart()
        {
            Start = true;
            return this;
        }

        public Node SetAsEnd()
        {
            End = true;
            return this;
        }
    }
}
