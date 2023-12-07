function check() {
	var mA = document.getElementById("m_A").value==''?0:document.getElementById("m_A").value;
	var mB = document.getElementById("m_B").value==''?0:document.getElementById("m_B").value;
	var mC = document.getElementById("m_C").value==''?0:document.getElementById("m_C").value;
	var mD = document.getElementById("m_D").value==''?0:document.getElementById("m_D").value;
	var mE = document.getElementById("m_E").value==''?0:document.getElementById("m_E").value;
	var mF = document.getElementById("m_F").value==''?0:document.getElementById("m_F").value;
	var times = document.getElementById("times").value==''?1:document.getElementById("times").value;
	
	

	if (isInteger(mA) && isInteger(mB) && isInteger(mC) && isInteger(mD) && isInteger(mE) && isInteger(mF) && isInteger(
			times)) {
		var sum = parseInt(mA) + parseInt(mB) + parseInt(mC) + parseInt(mD) + parseInt(mE) + parseInt(mF);
		if ((sum <= 100) && (sum > 0)) {
			if ((parseInt(times) > 0) && (parseInt(times) <= 1000)) {
				var materials = new Array;
				materials[0] = parseInt(mA);
				materials[1] = parseInt(mB);
				materials[2] = parseInt(mC);
				materials[3] = parseInt(mD);
				materials[4] = parseInt(mE);
				materials[5] = parseInt(mF);
				materials[6] = parseInt(times);
				console.log(materials);
				// 页面跳转
				window.location.href = "./html/Draw.html?mat=" + materials.toString();
				//alert("验证通过" + materials)
			} else {
				alert("配料次数为: " + times + "次, 请保持在1000以内!");
			}
		} else {
			alert("材料总数量为: " + sum + "kg, 请保持在100以内!");
		}
	} else {
		alert("请输入正整数！");
	}
}

function isInteger(n) {
	if (!(/(^[0-9]\d*$)/.test(n))) {
		return false;
	} else {
		return true;
	}
}
