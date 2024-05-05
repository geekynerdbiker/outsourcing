using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace CAB201_Assignment.Obstacles.Nodes
{
    public class Node : Coordinate
    {
        public Node? Parent { get; set; }
        public char Marker { get; set; }
        public float DistanceToTarget { get; set; } // H cost, the distance from the current node to the goal node.
        public float Weight { get; set; }
        public float Cost { get; set; } // G cost, the distance from the current node to the start node
        public bool Start = false;
        public bool End = false;
        public bool Solid;
        public bool Open;
        public bool Closed;

        public float F // F Cost (G + H cost), it is also the most important cost
        {
            get
            {
                if (DistanceToTarget != -1 && Cost != -1)
                    return DistanceToTarget + Cost;
                else
                    return -1;
            }
        }
        
        // TODO: Clean up this part of the code.
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
