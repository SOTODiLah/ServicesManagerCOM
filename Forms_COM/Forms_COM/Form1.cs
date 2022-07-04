using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Forms_COM
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            try
            {
                IFactoryServiceManagers factory;
                IServiceManager[] services;
                Type typeFactory = Type.GetTypeFromCLSID(new Guid(GuidsCOM.CLSID_FactoryServiceManager));
                factory = Activator.CreateInstance(typeFactory) as IFactoryServiceManagers;
                if (factory == null)
                    throw new ArgumentException("COM did't be connect");
                services = factory.GetAllServiceManagers().Cast<IServiceManager>().ToArray();
                dataGridView1.Rows.Add(services.Length);
                for (int i = 0; i < services.Length; i++)
                {
                    dataGridView1.Rows[i].Tag = services[i];
                    dataGridView1.Rows[i].SetValues(services[i].GetServiceFullName(), services[i].GetServiceStatus().ToString(), services[i].GetServiceType().ToString());
                }
                
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
                Environment.Exit(1);
            }
        }

        private void toolStripMenuStart_Click(object sender, EventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    if (item.ServiceStart())
                    {
                        item.WaitForServiceStatus(EServiceStatus.Running, 2000);
                        dataGridView1.SelectedRows[0].Cells[1].Value = item.GetServiceStatus();
                    }
                    else
                        MessageBox.Show(this, "Не удалось", item.ToString());
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }

        private void toolStripMenuStop_Click(object sender, EventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    if (item.ServiceStop())
                    {
                        item.WaitForServiceStatus(EServiceStatus.Running, 2000);
                        dataGridView1.SelectedRows[0].Cells[1].Value = item.GetServiceStatus();
                    }
                    else
                        MessageBox.Show(this, "Не удалось", item.ToString());
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }

        private void toolStripMenuPause_Click(object sender, EventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    if (item.ServicePause())
                    {
                        item.WaitForServiceStatus(EServiceStatus.Running, 2000);
                        dataGridView1.SelectedRows[0].Cells[1].Value = item.GetServiceStatus();
                    }
                    else
                        MessageBox.Show(this, "Не удалось", item.ToString());
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }

        private void toolStripMenuContinue_Click(object sender, EventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    if (item.ServiceContinue())
                    {
                        item.WaitForServiceStatus(EServiceStatus.Running, 2000);
                        dataGridView1.SelectedRows[0].Cells[1].Value = item.GetServiceStatus();
                    }
                    else
                        MessageBox.Show(this, "Не удалось", item.ToString());
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }

        private void toolStripMenuProperty_Click(object sender, EventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    string text = "Имя: " + item.GetServiceName();
                    text += "\n\nОтображаемое имя: " + item.GetServiceFullName();
                    text += "\n\nТип: " + item.GetServiceType().ToString();
                    text += "\n\nОписание:\n" + item.GetServiceDescription();
                    MessageBox.Show(text, "Свойства");
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            try
            {
                var item = dataGridView1.SelectedRows[0].Tag as IServiceManager;
                if (item != null)
                {
                    var status = item.GetServiceStatus();
                    bool canPauseContinue = item.CanServicePauseContinue();
                    contextMenuStrip1.Items[0].Enabled = status == EServiceStatus.Stopped;
                    contextMenuStrip1.Items[1].Enabled = item.CanServiceStop() && status != EServiceStatus.Stopping;
                    contextMenuStrip1.Items[2].Enabled = status == EServiceStatus.Running && canPauseContinue;
                    contextMenuStrip1.Items[3].Enabled = status == EServiceStatus.Paused && canPauseContinue;
                    dataGridView1.SelectedRows[0].Cells[1].Value = status.ToString();
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString(), "Error");
            }
        }
    }
}
