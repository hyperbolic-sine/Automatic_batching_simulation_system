var loc = location.href;
var str = decodeURI(loc.substr(loc.indexOf('=') + 1, loc.length - loc.indexOf('=')));
var matStr = str.split(',');
const materials = new Array;
for (var i = 0; i < matStr.length; i++) {
	materials[i] = parseInt(matStr[i]);
}

var ABS = document.getElementById("ActiveX");
if (ABS.object == null) {
	alert("ActiveX插件未安装!");
}

setTimeout(function() {
	run = ABS.SetCtrlParam(materials[0], materials[1], materials[2], materials[3], materials[4], materials[5], materials[6]);
	if (run) {
		alert("数据正在存入数据库。。。3秒后开始模拟!");
		// try{
		// 	// 连接MySQL
		// 	var con = new ActiveXObject("ADODB.Connection");
		// 	var host = "127.0.0.1;";
		// 	var user = "root;";
		// 	var password = "Dilanxue&*943;";
		// 	var database = "absdata;";
		// 	var port = "3307;"
		// 	// 连接字符串
		// 	var ConnectionString = "DRIVER={MySQL ODBC 8.0 Unicode Driver};Server=" + host + "User=" + user + "Password=" + password + "Database=" + database + "Option=3;Port=" + port;
		// 	con.open(ConnectionString);
			
		// 	// 向数据库中插入数据
		// 	var sql = "insert into absdata.materials(Material_A, Material_B, Material_C, Material_D, Material_E, Material_F, CycleCriterion) values (";
		// 	for (var i = 0; i < materials.length - 1; i++) {
		// 		sql = sql + materials[i] + ", ";
		// 	}
		// 	sql = sql + materials[6] + ")";
		// 	console.log(sql);
		// 	con.execute(sql);
		// 	// 完成数据存储，关闭连接
		// 	con.close();
		// 	con = null;
		// }catch(e){
		// 	//TODO handle the exception
		// 	console.log(e.message);
		// 	// document.write(e.message);
		// 	alert("数据保存失败!");
		// }
	} else {
		alert("模拟失败!");
	}
}, 1000);

function StopRun() {
	var stop = ABS.StopBtn();
	if (stop) {
		alert("模拟停止!");
		window.location.href = "../index.html";
	}
}
