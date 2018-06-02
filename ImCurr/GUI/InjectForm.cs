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
    public partial class InjectForm : Form
    {
        public InjectForm()
        {
            InitializeComponent();
        }

        FileInfo injFile;
        FileInfo conFile;
        FileInfo ejFile;

        void Inject(FileInfo src, FileInfo dest)
        {
            string tocpy = "";
            string realdest = "";
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
            File.Copy(dest.FullName, realdest, true);
            if (engInfo.Exists)
            {
                ProcessStartInfo launch = new ProcessStartInfo
                {
                    FileName = "icengine.exe"
                };
                string args = tocpy + " " + realdest + " 4";
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
            MessageBox.Show("Succesfully injected file!", "Result", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        void Eject(FileInfo src, string dest)
        {
            string tocpy = "";
            string realdest = "";
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
            for (int i = 0; i < dest.Length; i++)
            {
                if (dest[i] != ' ')
                {
                    realdest += dest[i];
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
                string args = tocpy + " " + realdest + " 5";
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
            MessageBox.Show("Succesfully ejected file!", "Result", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void selinjBtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (openFile.ShowDialog() != DialogResult.Cancel)
                {
                    string rawname = openFile.FileName;
                    try
                    {
                        injFile = new FileInfo(rawname);
                    }
                    catch (ArgumentException)
                    {
                        MessageBox.Show("Cannot open selected file!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                    if ((injFile.Name == "icengine.exe" || injFile.Name == AppDomain.CurrentDomain.FriendlyName) && (injFile.Directory.FullName == Environment.CurrentDirectory))
                    {
                        MessageBox.Show("Are you a retard?", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                }
                else
                    return;
            }
            catch (IOException)
            {
                MessageBox.Show("Error while getting a file, please change file name or try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            label1.Text = injFile.Name;
            selrecBtn.Enabled = true;
        }

        private void selrecBtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (openFile.ShowDialog() != DialogResult.Cancel)
                {
                    string rawname = openFile.FileName;
                    try
                    {
                        conFile = new FileInfo(rawname);
                    }
                    catch (ArgumentException)
                    {
                        MessageBox.Show("Cannot open selected file!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                    if ((conFile.Name == "icengine.exe" || conFile.Name == AppDomain.CurrentDomain.FriendlyName) && (conFile.Directory.FullName == Environment.CurrentDirectory))
                    {
                        MessageBox.Show("Are you a retard?", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                }
                else
                    return;
            }
            catch (IOException)
            {
                MessageBox.Show("Error while getting a file, please change file name or try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            label2.Text = conFile.Name;
            injBtn.Enabled = true;
            selinjBtn.Enabled = false;
            selrecBtn.Enabled = false;
        }

        private void selejBtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (openFile.ShowDialog() != DialogResult.Cancel)
                {
                    string rawname = openFile.FileName;
                    try
                    {
                        ejFile = new FileInfo(rawname);
                    }
                    catch (ArgumentException)
                    {
                        MessageBox.Show("Cannot open selected file!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                    if ((ejFile.Name == "icengine.exe" || ejFile.Name == AppDomain.CurrentDomain.FriendlyName) && (ejFile.Directory.FullName == Environment.CurrentDirectory))
                    {
                        MessageBox.Show("Are you a retard?", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    }
                }
                else
                    return;
            }
            catch (IOException)
            {
                MessageBox.Show("Error while getting a file, please change file name or try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            label3.Text = ejFile.Name;
            ejBtn.Enabled = true;
            destBox.Enabled = true;
        }
        
        private void injBtn_Click(object sender, EventArgs e)
        {
            Inject(injFile, conFile);
        }

        private void ejBtn_Click(object sender, EventArgs e)
        {
            Eject(ejFile, destBox.Text);
        }
    }
}
