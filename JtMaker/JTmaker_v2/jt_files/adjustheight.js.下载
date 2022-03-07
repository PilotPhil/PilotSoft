/**
 * 
 * @authors dxie (natcube@gmail.com)
 * @date    2014-12-27 08:24:31
 * @version 2014-12-27 08:24:31
 */
window.onload = function(){
	//parent.adjustHeight(485);
	try{
		adjustParentHeight();
	}catch(e){
		if(console) console.log('error:' + e);
	}
};

function setParentHeight(height){
	parent.adjustHeight(height);
}

function adjustParentHeight(){
	var maxLeftHeight=550;
	var currentHeight=$(document.body).height();
	var iframeHeight=currentHeight<maxLeftHeight?maxLeftHeight:currentHeight;
	parent.adjustHeight(iframeHeight);
}