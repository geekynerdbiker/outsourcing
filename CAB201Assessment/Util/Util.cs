using CAB201_Assignment.Obstacles.Nodes;
using System.Globalization;

namespace Util
{
    public class InvalidInput : Exception
    {
        public InvalidInput() { }

        public InvalidInput(string message)
            : base(message) { }

        public InvalidInput(string message, Exception inner)
            : base(message, inner) { }
    }
    public class Input
    {
        /// <summary>
        /// Prompts the user for coordinates as an x,y pair. Example input: 1,2
        /// </summary>
        /// <returns>
        /// An array of integers representing the coordinates where index of 0 and 1
        /// represents the x and y coordinates inputted by the user.
        /// </returns>
        /// <example>
        /// The following code demonstrates how to use the method
        /// <code>
        /// int[] input = PromptCoordinates("Enter the position of the Guard (X,Y)")
        /// input[0] // x
        /// input[1] // y
        /// </code>
        /// </example>
        /// 

        public static Coordinate PromptCoordinate(string prompt)
        {
            int[] coordinateArray = PromptCoordinateArray(prompt);
            return new Coordinate(coordinateArray[0], coordinateArray[1]);
        }
        public static int[] PromptCoordinateArray(string prompt)
        {
            string input = PromptString(prompt);
            return CoordinateStringToIntArray(input);
        }

        public static char PromptChar(string prompt)
        {
            string input = PromptString(prompt);
            return StringToChar(input);
        }

        public static double PromptDouble(string prompt)
        {
            string input = PromptString(prompt);
            return StringToFloat(input);
        }

        public static string PromptString(string prompt)
        {
            Console.WriteLine(prompt);
            string? input = Console.ReadLine();
            if (string.IsNullOrEmpty(input))
            {
                throw new InvalidInput();
            }
            return input;
        }

        private static int[] CoordinateStringToIntArray(string inputCoordinates)
        {
            string[] coordinates = inputCoordinates.Split(",");
            // TODO: One misuse of this funciton is if the coordinates is specified like this 1,,2, this should raise an Exception.
            int x = int.Parse(coordinates[0]);
            int y = int.Parse(coordinates[1]);

            return new int[] { x, y };
        }

        public static char StringToChar(string input)
        {
            char[] inputCharArray = input.ToCharArray();
            if (inputCharArray.Length > 1 || inputCharArray.Length == 0)
            {
                throw new InvalidInput();
            }
            return inputCharArray[0];
        }

        public static double StringToFloat(string input)
        {
            return double.Parse(input, CultureInfo.InvariantCulture.NumberFormat);
        }
    }
}
