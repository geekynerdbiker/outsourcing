using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public enum GameMode
    {
        None,
        Lobby,
        Town,
        Field
    }

    class Game
    {
        private GameMode mode = GameMode.Lobby;
        private Player player = null;

        public void Process()
        {
            switch (mode)
            {
                case GameMode.Lobby:
                    ProcessLobby();
                    break;

                case GameMode.Town:
                    ProcessTown();
                    break;

                case GameMode.Field:
                    ProcessField();
                    break;
            }
        }

        public void ProcessLobby()
        {
            Console.WriteLine("Select class");
            Console.WriteLine("1. Knight");
            Console.WriteLine("2. Archer");
            Console.WriteLine("3. Mage");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    player = new Knight();
                    mode = GameMode.Town;
                    break;

                case "2":
                    player = new Archer();
                    mode = GameMode.Town;
                    break;

                case "3":
                    player = new Mage();
                    mode = GameMode.Town;
                    break;
            }
        }

        public void ProcessTown() {
            Console.WriteLine("Entered to Town!");
            Console.WriteLine("1. Go Field");
            Console.WriteLine("2. Back to Lobby");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    mode = GameMode.Field;
                    break;

                case "2":
                    mode = GameMode.Lobby;
                    break;
            }
            }
        public void ProcessField() { }
}
