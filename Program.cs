using System;

namespace ConsoleApp1
{
    class Program
    {
        enum ClassType
        {
            None = 0,
            Knight = 1,
            Archer = 2,
            Mage = 3
        }

        static ClassType ChooseClass()
        {
            ClassType choice = ClassType.None;

            Console.WriteLine("Select a class!");
            Console.WriteLine("[1] Knight");
            Console.WriteLine("[2] Archer");
            Console.WriteLine("[3] Mage");

            string input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    choice = ClassType.Knight;
                    break;

                case "2":
                    choice = ClassType.Archer;
                    break;

                case "3":
                    choice = ClassType.Mage;
                    break;
            }

            return choice;
        }

        static void CreatePlayer(ClassType choice, out int hp, out int attack)
        {
            hp = 0; attack = 0;

            switch (choice)
            {
                case ClassType.Knight:
                    hp = 100;
                    attack = 10;
                    break;

                case ClassType.Archer:
                    hp = 75;
                    attack = 15;
                    break;

                case ClassType.Mage:
                    hp = 50;
                    attack = 20;
                    break;

                default:
                    hp = 0;
                    attack = 0;
                    break;
            }
        }

        static void Main(string[] args)
        {

            while (true)
            {
                ClassType choice = ChooseClass();
                if (choice != ClassType.None)
                {
                    int hp, attack;
                    CreatePlayer(choice, out hp, out attack);

                    Console.WriteLine($"HP{hp} Attack{attack}");
                }
            }
        }
    }
}
