using CAB201_Assignment.ObstacleMap;
using Util;
using Obstacles;

class Program
{
    private static NodeMap _nodeMap = new NodeMap();
    private static bool loopCompleted = false;
    static void Main(string[] args)
    {
        DisplayLoop();
    }
        
    private static void DisplayLoop()
    {
        while (!loopCompleted)
        {
            try
            {
                char input = DisplayPrompt();
                CodeSelector(input);
                if (input == 'x') { break; }
            }
            catch (InvalidInput)
            {
                Console.WriteLine("Invalid option.");
            }
        }
    }

    private static char DisplayPrompt()
    {
        Console.WriteLine("Select one of the following options");
        Console.WriteLine("g) Add 'Guard' obstacle");
        Console.WriteLine("f) Add 'Fence' obstacle");
        Console.WriteLine("s) Add 'Sensor' obstacle");
        Console.WriteLine("c) Add 'Camera' obstacle");
        Console.WriteLine("d) Show safe directions");
        Console.WriteLine("m) Display obstacle map");
        Console.WriteLine("p) Find safe path");
        char input = Input.PromptChar("x) Exit");
        return input;
    }

    private static void CodeSelector(char input)
    {
        switch(input)
        {
            // I have implemented alot of methods, but I think this one is the most readable out of all of them.
            case Guard.Marker:
                _nodeMap.AddObstacle(new Guard());
                break;
            case Fence.Marker:
                _nodeMap.AddObstacle(new Fence());
                break;
            case Camera.Marker:
                _nodeMap.AddObstacle(new Camera());
                break;
            case Sensor.Marker:
                _nodeMap.AddObstacle(new Sensor());
                break;
            case 'd':
                _nodeMap.ShowSafeDirections();
                break;
            case 'm':
                _nodeMap.DisplayObstacleMap();
                break;
            case 'p':
                _nodeMap.FindSafePath();
                break;
            default:
                Console.WriteLine("Invalid option.");
                break;
        }
    }
}
