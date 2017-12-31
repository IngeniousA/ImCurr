﻿using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace IC5
{
    class Program
    {
        static string[] names = new string[512];
        static int number = 0;
        static int[] sizes = new int[512];
        static int[] toskips = new int[512];
        static int toskip = 0;

        enum FileType
        {
            Other = 0,
            Encrypted = 1,
            Container = 2
        }

        public static String SHA256(String value)
        {
            using (SHA256 hash = System.Security.Cryptography.SHA256.Create())
            {
                return string.Concat(hash
                  .ComputeHash(Encoding.UTF8.GetBytes(value))
                  .Select(item => item.ToString("x2")));
            }
        }

        static void ContainerView(FileInfo container)
        {
            StreamReader hreader = new StreamReader(container.Name);
            //string[] names = new string[512];
            //long[] sizes = new long[512];
            char c = '1';
            string name = "";
            int num = 0;
            string numS = "";
            char[] h = new char[65];
            hreader.ReadBlock(h, 0, 65);
            toskip += 65;
            while (c != '\0')
            {
                c = (char)hreader.Read();
                if (c != '\0')
                {
                    name += c;
                    toskip++;
                }
            }
            toskip++;
            c = '1';
            while (c != '\0')
            {
                c = (char)hreader.Read();
                if (c != '\0')
                {
                    numS += c;
                    toskip++;
                }
            }
            toskip++;
            c = '1';
            num = Convert.ToInt32(numS);
            for (int i = 0; i < num; i++)
            {
                while (c != '\0')
                {
                    c = (char)hreader.Read();
                    if (c != '\0')
                    {
                        names[i] += c;
                        toskip++;
                    }
                }
                toskip++;
                c = '1';
                numS = "";
                while (c != '\0')
                {
                    c = (char)hreader.Read();
                    if (c != '\0')
                    {
                        numS += c;
                        toskip++;
                    }
                }
                toskip++;
                sizes[i] = Convert.ToInt32(numS);
                c = '1';
            }

            Console.WriteLine("CONTAINER \"" + name + "\":");
            Console.WriteLine("FILES: " + num);
            for (int i = 1; i <= num; i++)
            {
                Console.WriteLine("FILE #" + i + ": " + names[i - 1] + ", size: " + sizes[i - 1] + " bytes");
            }
            number = num;
            names[num] = name;
            hreader.Close();
        }

        static bool ValidPass(string toCheck)
        {
            if (toCheck.Any().Equals(' '))
            {
                return false;
            }
            return true;
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
            string hashed = SHA256(toCheck);
            if (pwdS == hashed)
            {
                return true;
            }
            return false;
        }

        static void CreateContainer(FileInfo[] c, string name, string pwd)
        {
            FileInfo engInfo = new FileInfo("icengine.exe");
            if (engInfo.Exists)
            {
                string args = "";
                args += name + " " + pwd + " ";
                for (int i = c.GetLength(0) - 1; i >= 0; i--)
                {
                    args += c[i].Name + " ";
                }
                args += c.GetLength(0) + " " + "2";
                ProcessStartInfo launch = new ProcessStartInfo
                {
                    FileName = "icengine.exe",
                    Arguments = args
                };
                Process.Start(launch);
                FileInfo readyStat = new FileInfo("ready.icsys");
                while (!readyStat.Exists)
                {
                    readyStat.Refresh();
                    Thread.Sleep(500);
                }
                for (int i = 0; i < c.GetLength(0); i++)
                {
                    File.Delete(c[i].Name);
                }
                File.Delete("ready.icsys");
            }
            else
            {
                Console.WriteLine("Error: icengine.exe was modified or deleted.");
                Console.Read();
            }
        }

        static void Unpack(FileInfo confile, string conpwd)
        {
            File.Copy(confile.Name, names[number] + ".ictTMP");
            FileInfo tmp = new FileInfo(names[number] + ".ictTMP");
            FileInfo engInfo = new FileInfo("icengine.exe");
            if (engInfo.Exists)
            {
                string args = "";
                args += confile.Name + " " + conpwd + " " + number + " ";
                for (int i = number - 1; i >= 0; i--)
                {
                    toskips[i] = toskip;
                    for (int j = 0; j < i; j++)
                    {
                        toskips[i] += sizes[j];
                    }
                    for (int j = 0; j < names[i].Length; j++)
                    {
                        if (names[i][j] == ' ')
                        {
                            args += '_';
                        }
                        else
                        {
                            args += names[i][j];
                        }
                    }
                    args += " " + toskips[i] + " ";
                }
                args += "3";
                ProcessStartInfo launch = new ProcessStartInfo
                {
                    FileName = "icengine.exe",
                    Arguments = args
                };
                Process.Start(launch);
                FileInfo readyStat = new FileInfo("ready.icsys");
                while (!readyStat.Exists)
                {
                    readyStat.Refresh();
                    Thread.Sleep(500);
                }
                File.Delete(confile.Name);
                File.Copy(names[number] + ".ictTMP", confile.Name);
                File.Delete(names[number] + ".ictTMP");
                File.Delete("ready.icsys");
            }
            else
            {
                Console.WriteLine("Error: icengine.exe was modified or deleted.");
                Console.Read();
            }
        }

        static void EDEngine(FileInfo src, FileInfo dest, string pwd, char isEncrypt)
        {
            FileInfo engInfo = new FileInfo("icengine.exe");
            if (engInfo.Exists)
            {
                ProcessStartInfo launch = new ProcessStartInfo
                {
                    FileName = "icengine.exe"
                };
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
        static string CreateContainerHeader(FileInfo[] dir, string pwd, string cname)
        {
            string res = "";
            string chash = SHA256(pwd);
            res += chash + '\0';
            res += cname + '\0';
            res += dir.GetLength(0);
            res += '\0';
            for (int i = 0; i < dir.GetLength(0); i++)
            {
                res += dir[i].Name + '\0' + dir[i].Length + '\0';
            }
            return res;
        }

        static void SendHeader(string h, string to)
        {
            File.WriteAllText(to, h);
        }

        static FileType ExtAnalysis(string source)
        {
            if ((source == ".scsn") || (source == ".icf"))
            {
                return FileType.Encrypted;
            }
            else if (source == ".ict")
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

        [STAThread] //без этого не работает
        static void Main(string[] args)
        {
            FileType fileStatus = 0;
            string choice = "\0";
            FileInfo single = null;
            DirectoryInfo cdir;
            FileInfo[] container;
            FileInfo dest;

            Console.Title = "ImCurr 0.5";
            Console.WriteLine("ImCurr 0.5\nMade by Sergey \'Ingenious\' Rakhmanov\n\n");

            Console.WriteLine("1 - Open a file");
            Console.WriteLine("2 - Create a container");
            Console.WriteLine("0 - Exit");

            choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    Console.WriteLine("Enter file name:");

                    OpenFileDialog openFile = new OpenFileDialog
                    {
                        Filter = "All files| *.*|Encrypted files (*.scsn, *.icf) | *.scsn, *.icf|Containers (*.ict) | *.ict"
                    };

                    OPEN_FILE: openFile.ShowDialog(); //диалог выбора файла (ваш кэп)

                    string rawname = openFile.FileName;

                    try
                    {
                        single = new FileInfo(rawname);
                    }
                    catch (System.ArgumentException) //выбросит, если пользователь ничего не выберет
                    {
                        Console.WriteLine("\nPath is incorrect");
                        Console.WriteLine("1 - Retry");
                        Console.WriteLine("2 - Exit");
                        string choice_file = Console.ReadLine();

                        switch (choice_file)
                        {
                            case "1":
                                goto OPEN_FILE; //здесь мы вернёмся к выбору диалога
                            case "2":
                                Environment.Exit(0);
                                break;
                            default:
                                goto OPEN_FILE; //вновь вернёмся к выбору диалога                     
                        }

                    }

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
                            Console.WriteLine("Enter password:");
                            ConsoleKeyInfo key;
                            string pass = "";
                            do
                            {
                                key = Console.ReadKey(true);
                                if (key.Key != ConsoleKey.Spacebar)
                                {
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
                            }
                            while (key.Key != ConsoleKey.Enter);

                            Console.WriteLine();
                            if (BypassCheck(single, pass))
                            {
                                ContainerView(single);
                                Console.WriteLine("\n 1 - Unpack \n 2 - Rename files \n 3 - Close");
                                string conc = Console.ReadLine();
                                switch(conc)
                                {
                                    case "1":
                                        Unpack(single, pass);
                                        break;
                                    case "2":

                                        break;
                                    case "3":

                                        break;
                                    default:

                                        break;
                                }
                                //Console.ReadLine();
                            }
                            else
                            {
                                Console.Write("Incorrect password!");
                                Console.ReadLine();
                                Environment.Exit(0);
                            }
                        }
                        else
                        {
                            Console.WriteLine("Enter password:");
                            ConsoleKeyInfo key;
                            string pass = "";
                            do
                            {
                                key = Console.ReadKey(true);
                                if (key.Key != ConsoleKey.Spacebar)
                                {
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
                            }
                            while (key.Key != ConsoleKey.Enter);
                            if (ValidPass(pass))
                            {
                                Console.WriteLine();
                                Console.WriteLine("Enter destination file name:");
                                string destname = Console.ReadLine();
                                destname += ".icf";
                                dest = new FileInfo(destname);
                                EDEngine(single, dest, pass, '1');
                            }
                            else
                            {
                                Console.WriteLine("Invalid password!");
                                Console.ReadLine();
                            }
                        }
                    }
                    break;
                case "2":
                    Console.WriteLine("Enter directory name:");

                    var folderOpen = new FolderBrowserDialog();
                    OPEN_FOLDER: folderOpen.ShowDialog(); //покажем выбор папки 

                    string cdirname = null;

                    try // в идеале лучше вообще всё вынести в try-catch, но обойдемся goto
                    {
                        cdirname = folderOpen.SelectedPath;
                    }
                    catch (System.ArgumentException)
                    {
                        Console.WriteLine("\nIncorrect input");
                        Console.WriteLine("1 - Retry");
                        Console.WriteLine("0 - Exit");
                        string choice_dir = Console.ReadLine();
                        switch (choice_dir)
                        {
                            case "1":
                                goto OPEN_FOLDER;
                            case "0":
                                Environment.Exit(0);
                                break;
                            default:
                                goto OPEN_FOLDER;
                        }
                    }

                    cdir = new DirectoryInfo(cdirname);
                    if (cdir.Exists)
                    {
                        container = cdir.GetFiles();
                        Console.WriteLine("Enter container name:");
                        string cname = Console.ReadLine();
                        Console.WriteLine("Enter container password:");
                        ConsoleKeyInfo key;
                        string conpwd = "";
                        do
                        {
                            key = Console.ReadKey(true);

                            if (key.Key != ConsoleKey.Spacebar)
                            {
                                if (key.Key != ConsoleKey.Backspace && key.Key != ConsoleKey.Enter)
                                {
                                    conpwd += key.KeyChar;
                                    Console.Write("*");
                                }
                                else
                                {
                                    if (key.Key == ConsoleKey.Backspace && conpwd.Length > 0)
                                    {
                                        conpwd = conpwd.Substring(0, (conpwd.Length - 1));
                                        Console.Write("\b \b");
                                    }
                                }
                            }
                        }
                        while (key.Key != ConsoleKey.Enter);

                        Console.WriteLine();
                        string header = CreateContainerHeader(container, conpwd, cname);
                        cname += ".ict";
                        SendHeader(header, cname);
                        for (int i = 0; i < container.GetLength(0); i++)
                        {
                            if (!File.Exists(Environment.CurrentDirectory + "\\" + container[i].Name))
                            {
                                container[i].CopyTo(Environment.CurrentDirectory + "\\" + container[i].Name);
                            }
                            else
                            {
                                Console.WriteLine("Error: Cannot move file, already exists one.");
                                Environment.Exit(0);
                            }
                        }
                        CreateContainer(container, cname, conpwd);

                        //Console.ReadLine();
                    }
                    else
                    {
                        Console.WriteLine("Error: directory does not exist");
                        Console.ReadLine();
                    }
                    break;
                case "0":
                    Environment.Exit(0);
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