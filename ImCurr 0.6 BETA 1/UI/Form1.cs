using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI6
{
    public partial class mainForm : Form
    {
        enum FileType
        {
            Basic = 0,
            Encrypted = 1,
            Container = 2,
            Folder = 3,
            Old = 4,
            Empty = -1
        }

        char emptyChar;
        string tocpy = "";
        string realdest = "";
        static FileInfo single;
        static DirectoryInfo cdir;
        static FileInfo[] container;

        static string[] names = new string[512];
        static int number = 0;
        static int[] sizes = new int[512];
        static int[] toskips = new int[512];
        static int toskip = 0;
        FileType ftype;

        string strType(FileType ft)
        {
            switch (ft)
            {
                case FileType.Basic:
                    return "other";
                case FileType.Encrypted:
                    return "encrypted";
                case FileType.Container:
                    return "container";
                case FileType.Folder:
                    return "folder";
                case FileType.Old:
                    return "old";
                case FileType.Empty:
                    return "empty";
                default:
                    return "wtf";
            }
        }

        void Log(string text)
        {
            logBox.Items.Add(text);
        }

        void Log(string text, byte mode)
        {
            string res = "";
            switch (mode)
            {
                case 0: //INFO
                    res += "INFO: ";
                    break;
                case 1: //OK
                    res += "SUCCESS: ";
                    break;
                case 2: //WARNING
                    res += "WARNING: ";
                    break;
                case 3: //ERROR
                    res += "ERROR: ";
                    break;
                default:
                    break;
            }
            res += text;
            logBox.Items.Add(res);
        }

        void SwitchUI(FileType ft)
        {
            if (ft == FileType.Empty)
            {
                actionBtn.Text = "No file selected";
                nameBox.Text = "Output file name";
                pwdBox.PasswordChar = emptyChar;
                pwdBox.Text = "Password";
                nameBox.ForeColor = Color.Gray;
                Font x = new Font(nameBox.Font, FontStyle.Italic);
                nameBox.Font = x;
                pwdBox.ForeColor = Color.Gray;
                Font y = new Font(pwdBox.Font, FontStyle.Italic);
                pwdBox.Font = y;
                fileBtn.Enabled = true;
                dirBtn.Enabled = true;
                nameBox.Enabled = false;
                pwdBox.Enabled = false;
                actionBtn.Enabled = false;
            }
            else
            {
                switch (ft)
                {
                    case FileType.Basic:
                        fileBtn.Enabled = false;
                        dirBtn.Enabled = false;
                        nameBox.Enabled = true;
                        pwdBox.Enabled = true;
                        actionBtn.Enabled = true;
                        actionBtn.Text = "Encrypt";
                        Log("Enter output file name and password to encrypt");
                        break;
                    case FileType.Encrypted:
                        fileBtn.Enabled = false;
                        dirBtn.Enabled = false;
                        nameBox.Enabled = true;
                        pwdBox.Enabled = true;
                        actionBtn.Enabled = true;
                        actionBtn.Text = "Decrypt";
                        Log("Enter output file name and password to decrypt");
                        break;
                    case FileType.Container:
                        fileBtn.Enabled = false;
                        dirBtn.Enabled = false;
                        nameBox.Enabled = true;
                        pwdBox.Enabled = true;
                        actionBtn.Enabled = true;
                        actionBtn.Text = "Unpack";
                        Log("Enter output file name and password to unpack");
                        break;
                    case FileType.Folder:
                        fileBtn.Enabled = false;
                        dirBtn.Enabled = false;
                        nameBox.Enabled = true;
                        pwdBox.Enabled = true;
                        actionBtn.Enabled = true;
                        actionBtn.Text = "Pack";
                        Log("Enter output file name and password to pack");
                        break;
                    case FileType.Old:
                        fileBtn.Enabled = true;
                        dirBtn.Enabled = true;
                        nameBox.Enabled = false;
                        pwdBox.Enabled = false;
                        actionBtn.Enabled = false;
                        actionBtn.Text = "Old file detected";
                        Log("Cannot work with old files!", 3);
                        break;
                    default:

                        break;
                }
            }
        }

        public mainForm()
        {
            InitializeComponent();
        }

        void ED(FileInfo src, FileInfo dest, string pwd, char isEncrypt)
        {
            tocpy = "";
            realdest = "";
            FileInfo engInfo = new FileInfo("icengine.exe");
            for (int i = 0; i < src.Name.Length; i++)
            {
                if (src.Name[i] != ' ')
                {
                    tocpy += src.Name[i];
                }
                else
                {
                    tocpy += '_';
                }
            }
            for (int i = 0; i < dest.Name.Length; i++)
            {
                if (dest.Name[i] != ' ')
                {
                    realdest += dest.Name[i];
                }
                else
                {
                    realdest += '_';
                }
            }
            tocpy += '_';
            File.Copy(src.FullName, tocpy, true);
            if (engInfo.Exists)
            {
                ProcessStartInfo launch = new ProcessStartInfo
                {
                    FileName = "icengine.exe"
                };
                string args = tocpy + " " + realdest + " " + pwd + " " + isEncrypt;
                launch.Arguments = args;
                Process.Start(launch);
                FileInfo readyStat = new FileInfo("ready.icsys");
                while (!readyStat.Exists)
                { 
                    readyStat.Refresh();
                }
                File.Delete(tocpy);
                File.Delete("ready.icsys");
                ProcessStartInfo explorer = new ProcessStartInfo
                {
                    FileName = "explorer.exe",
                    Arguments = Environment.CurrentDirectory
                };
                Process.Start(explorer);
            }
            else
            {
                MessageBox.Show("Error: icengine.exe was modified or deleted.");
            }
            if (isEncrypt == '1')
                Log("Successfully encrypted file " + src.Name + "!", 1);
            else
                Log("Successfully decrypted file " + src.Name + "!", 1);
            SwitchUI(FileType.Empty);
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            emptyChar = pwdBox.PasswordChar;
            SwitchUI(FileType.Empty);
        }

        private void fileBtn_Click(object sender, EventArgs e)
        {
            OPEN_FILE:
            if (openFile.ShowDialog() != DialogResult.Cancel)
            {
                string rawname = openFile.FileName;
                try
                {
                    single = new FileInfo(rawname);
                }
                catch (ArgumentException)
                {
                    Log("Cannot open selected file!", 3);
                    goto OPEN_FILE;
                }
                if (single.Name == "icengine.exe" || single.Name == AppDomain.CurrentDomain.FriendlyName)
                {
                    Log("Are you a retard?", 3);
                    return;
                }
            }
            else
                return;            
            switch (single.Extension)
            {
                case ".ic6":
                    ftype = FileType.Encrypted;
                    break;
                default:
                    if (single.Extension == ".scsn" || single.Extension == ".ict" || single.Extension == ".icf")
                    {
                        ftype = FileType.Old;
                    }
                    else
                    {
                        ftype = FileType.Basic;
                    }
                    break;
            }
            if (ftype != FileType.Container)
            {
                if (single.Name.Length >= 25)
                    Log("Selected file " + single.Name.Substring(0, 25) + "..., size: " + single.Length + " bytes, type: " + strType(ftype), 1);
                else
                    Log("Selected file " + single.Name + ", size: " + single.Length + " bytes, type: " + strType(ftype), 1);
            }
            SwitchUI(ftype);
        }

        private void dirBtn_Click(object sender, EventArgs e)
        {
            ftype = FileType.Folder;
            var folderOpen = new FolderBrowserDialog();
            string cdirname = null;
            if (folderOpen.ShowDialog() != DialogResult.Cancel)
            {
                cdirname = folderOpen.SelectedPath;
                cdir = new DirectoryInfo(cdirname);
            }
            else
                return;
            container = cdir.GetFiles();
            long fsize = 0;
            for (int i = 0; i < container.Length; i++)
                fsize += container[i].Length;
            Log("Selected folder " + cdir.Name + ", size of files: " + fsize + " bytes.", 0);
            for (int i = 0; i < container.Length; i++)
                Log(" ├" + container[i].Name);
            SwitchUI(ftype);
        }

        private void nameBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (nameBox.Text == "Output file name")
            {
                nameBox.ForeColor = Color.Black;
                nameBox.Text = "";
                Font x = new Font(nameBox.Font, FontStyle.Regular);
                nameBox.Font = x;
            }            
        }

        private void pwdBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (pwdBox.Text == "Password")
            {
                pwdBox.PasswordChar = '*';
                pwdBox.ForeColor = Color.Black;
                pwdBox.Text = "";
                Font x = new Font(pwdBox.Font, FontStyle.Regular);
                pwdBox.Font = x;
            }
        }

        private void actionBtn_Click(object sender, EventArgs e)
        {
            string destname = nameBox.Text;
            string pass = pwdBox.Text;
            switch (ftype)
            {
                case FileType.Basic:
                    destname += ".ic6";
                    FileInfo dest = new FileInfo(destname);
                    ED(single, dest, pass, '1');
                    break;
                case FileType.Encrypted:
                    FileInfo destE = new FileInfo(destname);
                    ED(single, destE, pass, '0');
                    break;
                default:
                    if (ftype == FileType.Old || ftype == FileType.Empty || ftype == FileType.Container)
                    {
                        Log("Cannot implement this type of file in BETA 1", 2);
                    }
                    break;
            }
        }

        private void nameBox_TextChanged(object sender, EventArgs e)
        {
            if (nameBox.Text == "")
                actionBtn.Enabled = false;
            else if (!(pwdBox.Text == "" || pwdBox.Text == "Password"))
                actionBtn.Enabled = true;        
        }

        private void pwdBox_TextChanged(object sender, EventArgs e)
        {
            if (pwdBox.Text == "")
                actionBtn.Enabled = false;
            else if (!(nameBox.Text == "" || nameBox.Text == "Outpute file name"))
                actionBtn.Enabled = true;
        }
        
        private void pwdBox_Enter(object sender, EventArgs e)
        {
            if (pwdBox.Text == "Password")
            {
                pwdBox.PasswordChar = '*';
                pwdBox.ForeColor = Color.Black;
                pwdBox.Text = "";
                Font x = new Font(pwdBox.Font, FontStyle.Regular);
                pwdBox.Font = x;
            }
        }
    }
}
