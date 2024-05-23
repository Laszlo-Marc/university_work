using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Xml;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private SqlConnection conn;
        private DataSet ds;
        private BindingSource parentBindingSource;
        private BindingSource childBindingSource;
        private SqlDataAdapter parentDataAdapter;
        private SqlDataAdapter childDataAdapter;
        private SqlCommandBuilder commandBuilder;
        public Form1()
        {
            InitializeComponent();
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            // Load configuration from file
            
          
            // Parse configuration
            string connectionString = ConfigurationManager.ConnectionStrings["conn"].ConnectionString;
            string parentTableName = ConfigurationManager.AppSettings["ParentTable"];
            string childTableName = ConfigurationManager.AppSettings["ChildTable"];
            string parentColumn = ConfigurationManager.AppSettings["ParentID"]; 
            string childColumn = ConfigurationManager.AppSettings["ChildID"];
            string parentQuery = ConfigurationManager.AppSettings["ParentQuery"];
            string childQuery = ConfigurationManager.AppSettings["ChildQuery"];
         
            // Connect to database
            conn = new SqlConnection(connectionString);
            ds = new DataSet();

            // Load data
           
            try
            {
                // Load data
                parentDataAdapter = new SqlDataAdapter(parentQuery, conn);
                childDataAdapter = new SqlDataAdapter(childQuery, conn);
                parentDataAdapter.Fill(ds, parentTableName);
                childDataAdapter.Fill(ds, childTableName);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error occurred while loading data: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            // Set up parent child relationship
            DataRelation relation = new DataRelation("FK_PSY_Session",
                ds.Tables[parentTableName].Columns[parentColumn],
                ds.Tables[childTableName].Columns[childColumn]);
            ds.Relations.Add(relation);

            // Set up binding sources
            parentBindingSource = new BindingSource();
            childBindingSource = new BindingSource();

            parentBindingSource.DataSource = ds;
            parentBindingSource.DataMember = parentTableName;

            childBindingSource.DataSource = parentBindingSource;
            childBindingSource.DataMember = "FK_PSY_Session";

            // Bind data to DataGridViews
           psyDataGridView.DataSource = parentBindingSource;
           tsDataGridView.DataSource = childBindingSource;
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            try
            {
                // Update changes to the database
                string childTableName = ConfigurationManager.AppSettings["ChildTable"];
                // Configure commands
                commandBuilder = new SqlCommandBuilder(childDataAdapter);

                // Update the changes
                childDataAdapter.Update(ds, childTableName);

                MessageBox.Show("Update successful.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error occurred while updating data: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
