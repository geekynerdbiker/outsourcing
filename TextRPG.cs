using System;

namespace ConsoleApp1
{
    class Knight
    {
        public int hp;
        public int attack;
        public void Move()
        {
            Console.WriteLine("Knight Move");
        }
        public void Attack()
        {
            Console.WriteLine("Knight Attack");
        }
        public void Die() { }
    }

    class Program
    {
        enum ClassType
        {
            None = 0,
            Knight = 1,
            Archer = 2,
            Mage = 3
        }

        struct Player
        {
            public int hp;
            public int attack;
        }

        enum MonsterType
        {
            None = 0,
            Slime = 1,
            Orc = 2,
            Skelton = 3
        }

        struct Monster
        {
            public int hp;
            public int attack;
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

        static void CreatePlayer(ClassType choice, out Player player)
        {
            player.hp = 0; player.attack = 0;

            switch (choice)
            {
                case ClassType.Knight:
                    player.hp = 100;
                    player.attack = 10;
                    break;

                case ClassType.Archer:
                    player.hp = 75;
                    player.attack = 15;
                    break;

                case ClassType.Mage:
                    player.hp = 50;
                    player.attack = 20;
                    break;

                default:
                    player.hp = 0;
                    player.attack = 0;
                    break;
            }
        }

        static void CreateRandomMonster(out Monster monster)
        {
            Random rand = new Random();
            int randMonster = rand.Next(1, 4);

            switch (randMonster)
            {
                case (int)MonsterType.Slime:
                    Console.WriteLine("Slime spawned!");
                    monster.hp = 20;
                    monster.attack = 2;
                    break;

                case (int)MonsterType.Orc:
                    Console.WriteLine("Orc spawned!");
                    monster.hp = 40;
                    monster.attack = 4;
                    break;

                case (int)MonsterType.Skelton:
                    Console.WriteLine("Skeleton spawned!");
                    monster.hp = 30;
                    monster.attack = 3;
                    break;

                default:
                    monster.hp = 0;
                    monster.attack = 0;
                    break;
            }
        }

        static void EnterGame(ref Player player)
        {
            while (true)
            {
                Console.WriteLine("Server Connected!");
                Console.WriteLine("[1] Go Field");
                Console.WriteLine("[2] Go Lobby");

                string input = Console.ReadLine();
                switch (input)
                {
                    case "1":
                        EnterField(ref player);
                        break;
                    case "2":
                        return;
                }
            }
        }

        static void EnterField(ref Player player)
        {
            while (true)
            {
                Console.WriteLine("Entered!");

                Monster monster;
                CreateRandomMonster(out monster);

                Console.WriteLine("[1] Fight");
                Console.WriteLine("[2] Run away");

                string input = Console.ReadLine();
                switch (input)
                {
                    case "1":
                        Fight(ref player, ref monster);
                        break;
                    case "2":
                        RunAway(ref player, ref monster);
                        break;
                }
            }
        }

        static void Fight(ref Player player, ref Monster monster)
        {
            while (true)
            {
                monster.hp -= player.attack;
                if (monster.hp <= 0)
                {
                    Console.WriteLine($"Current HP: {player.hp}");
                    Console.WriteLine("Victory!");
                    break;
                }

                player.hp -= monster.attack;
                if (player.hp <= 0)
                {
                    Console.WriteLine("Lost...");
                    break;
                }

            }
        }

        static void RunAway(ref Player player, ref Monster monster)
        {
            Random rand = new Random();
            int runaway = rand.Next(1, 101);

            if (runaway <= 33)
                Console.WriteLine("Ran away successfully!");
            else
                Fight(ref player, ref monster);
        }

        static void Main(string[] args)
        {
            Knight knight = new Knight();

            knight.hp = 100;
            knight.attack = 10;

            knight.Move();
            knight.Attack();

            /*
            while (true)
            {
                ClassType choice = ChooseClass();
                if (choice == ClassType.None) continue;

                Player player;
                CreatePlayer(choice, out player);
                EnterGame(ref player);

            }*/
        }
    }
}
