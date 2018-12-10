using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace TPL_Program
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        private CancellationTokenSource cancelToken = new CancellationTokenSource();
        private void btnProcessImages_Click(object sender, EventArgs e)
        {
            Task.Factory.StartNew(() =>
            {
                ProcessFiles();
            }
            );


        }
        private void ProcessFiles()
        {
            ParallelOptions parOpts = new ParallelOptions();
            parOpts.CancellationToken = cancelToken.Token;
            parOpts.MaxDegreeOfParallelism = System.Environment.ProcessorCount;
            string[] files = Directory.GetFiles(@"F:\Svyatoslav\Оголошення", "*.jpg", SearchOption.AllDirectories);
            string newDir = @"F:\Svyatoslav\Оголошення";
            Directory.CreateDirectory(newDir);
            try
            {
                Parallel.ForEach(files, item =>
                    {
                        parOpts.CancellationToken.ThrowIfCancellationRequested();
                        string fileName = Path.GetFileName(item);
                        using (Bitmap bitmap = new Bitmap(item))
                        {

                            bitmap.RotateFlip(RotateFlipType.Rotate180FlipNone);
                            bitmap.Save(Path.Combine(newDir, fileName));
                            Invoke((Action)delegate
                            {
                                InformationTexBox.Text = string.Format("Processing {0} on thread {1}", fileName, Thread.CurrentThread.ManagedThreadId);
                            }
                            );
                        }
                    }
                    );
            }
            catch (OperationCanceledException ex)
            {
                Invoke((Action)delegate
                {
                    MessageBox.Show(ex.Message);
                });
            }
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            cancelToken.Cancel();
        }
    }
}
