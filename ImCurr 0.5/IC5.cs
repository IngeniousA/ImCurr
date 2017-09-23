using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace IC5
{
    class Program
    {
        enum FileType
        {
            Other = 0,
            Encrypted = 1,
            Container = 2
        }

        public static String sha256_hash(String value)
        {
            using (SHA256 hash = SHA256.Create())
            {
                return String.Concat(hash
                  .ComputeHash(Encoding.UTF8.GetBytes(value))
                  .Select(item => item.ToString("x2")));
            }
        }

        static bool BypassCheck(FileInfo file, string toCheck)
        {
            byte[] pwd = new byte[65];
            string pwdS = "";
            FileStream fs;
            fs = file.OpenRead();
            fs.Read(pwd, 0, 64);
            fs.Close();
            for (int i = 0; i < 64; i++)
            {
                pwdS += Convert.ToChar(pwd[i]);
            }
            string hashed = sha256_hash(toCheck);
            if (pwdS == hashed)
            {
                return true;
            }
            return false;
        }

        static void EDEngine(FileInfo src, FileInfo dest, string pwd, char isEncrypt)
        {
            FileInfo engInfo = new FileInfo("icengine.exe");
            if (engInfo.Exists)
            {
                ProcessStartInfo launch = new ProcessStartInfo();
                launch.FileName = "icengine.exe";
                string args = src.Name + " " + dest.Name + " " + pwd + " " + isEncrypt;
                launch.Arguments = args;
                Process.Start(launch);
            }
            else
            {
                Console.WriteLine("Error: icengine.exe was modified or deleted.");
                Console.Read();
            }
        }
        /*
        static void ContainerCreation();
        static void ContainerView();
        */
        static FileType ExtAnalysis(string source)
        {
            if ((source == ".scsn") || (source == ".icf"))
            {
                return FileType.Encrypted;
            }
            else if (source == ".icc")
            {
                return FileType.Container;
            }
            return FileType.Other;
        }

        static string ValidCheck(FileInfo file)
        {
            if (!file.Exists)
            {
                return "file does not exist";
            }
            if (file.IsReadOnly)
            {
                return "file is busy or [B]locked";
            }
            return "";
        }

        static void Main(string[] args)
        {
            FileType fileStatus = 0;
            string choice = "\0";
            FileInfo single;
            FileInfo dest;
            Console.Title = "ImCurr 0.5";
            Console.WriteLine("ImCurr 0.5\nMade by Sergey \'Ingenious\' Rakhmanov\n\n");
            Console.WriteLine("1 - Open a file");
            Console.WriteLine("2 - Create a container");
            choice  = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    Console.WriteLine("Enter file name:");
                    string rawname = Console.ReadLine();
                    single = new FileInfo(rawname);
                    fileStatus = ExtAnalysis(single.Extension);
                    Console.Write("Opening file... ");
                    if (ValidCheck(single) != "")
                    {
                        Console.Write("Error while opening file: " + ValidCheck(single));
                        Console.ReadLine();
                        Environment.Exit(0);
                    }
                    else
                    {
                        Console.WriteLine("OK");
                        if (fileStatus == FileType.Encrypted)
                        {
                            Console.WriteLine("Enter password:");
                            ConsoleKeyInfo key;
                            string pass = "";
                            do
                            {
                                key = Console.ReadKey(true);

                                if (key.Key != ConsoleKey.Backspace && key.Key != ConsoleKey.Enter)
                                {
                                    pass += key.KeyChar;
                                    Console.Write("*");
                                }
                                else
                                {
                                    if (key.Key == ConsoleKey.Backspace && pass.Length > 0)
                                    {
                                        pass = pass.Substring(0, (pass.Length - 1));
                                        Console.Write("\b \b");
                                    }
                                }
                            }
                            while (key.Key != ConsoleKey.Enter);

                            Console.WriteLine();
                            if (BypassCheck(single, pass))
                            {
                                Console.WriteLine("Enter destination file name:");
                                string destname = Console.ReadLine();
                                dest = new FileInfo(destname);
                                EDEngine(single, dest, pass, '0');
                            }
                            else
                            {
                                Console.Write("Incorrect password!");
                                Console.ReadLine();
                                Environment.Exit(0);
                            }
                        }
                        else if (fileStatus == FileType.Container)
                        {
                            //CONTAINER VIEW
                        }
                        else
                        {
                            Console.WriteLine("Enter password:");
                            ConsoleKeyInfo key;
                            string pass = "";
                            do
                            {
                                key = Console.ReadKey(true);

                                if (key.Key != ConsoleKey.Backspace && key.Key != ConsoleKey.Enter)
                                {
                                    pass += key.KeyChar;
                                    Console.Write("*");
                                }
                                else
                                {
                                    if (key.Key == ConsoleKey.Backspace && pass.Length > 0)
                                    {
                                        pass = pass.Substring(0, (pass.Length - 1));
                                        Console.Write("\b \b");
                                    }
                                }
                            }
                            while (key.Key != ConsoleKey.Enter);
                            Console.WriteLine();
                            Console.WriteLine("Enter destination file name:");
                            string destname = Console.ReadLine();
                            destname += ".icf";
                            dest = new FileInfo(destname);
                            EDEngine(single, dest, pass, '1');
                        }
                    }
                    break;  
                case "2":

                    break;
                default:
                    Console.Clear();
                    Console.WriteLine("Incorrect input!");
                    Console.ReadLine();
                    break;
            }
        }
    }
}
