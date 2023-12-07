var con = new ActiveXObject("ADODB.Connection");
var rs = new ActiveXObject("ADODB.Recordset");

var host = "127.0.0.1;";
var user = "root;";
var password = "Dilanxue&*943;";
var database = "absdata;";
var port = "3307;"
var ConnectionString = "DRIVER={MySQL ODBC 8.0 Unicode Driver};Server=" + host + "User=" + user + "Password=" + password + "Database=" + database + "Option=3;Port=" + port;
try{
	con.open(ConnectionString);
	
	var sql = "select * from absdata.materials";
	rs.open(sql, con);
	
	function Query(){
		var html = "";
		while(!rs.EOF){
			html = html + rs.Fields("id") + " " + rs.Fields("Material_A");
			rs.moveNext();
		}
		document.write(html);
	}
	
	function Insert(Material_A, Material_B, Material_C, Material_D, Material_E, Material_F, CycleCriterion){
		var Inssql = "insert into absdata.materials(Material_A, Material_B, Material_C, Material_D, Material_E, Material_F, CycleCriterion) values (" + 
		Material_A + "," + Material_B + "," + Material_C + "," + Material_D + "," + Material_E + "," + Material_F + "," + CycleCriterion + ")";
		console.log(Inssql);
		//rs.open(Inssql, con);
	}
	
	function Distory(){
		rs.close();
		rs = null;
		con.close();
		con = null;
	}
}catch(e){
	//TODO handle the exception
	document.write(e.message);
}