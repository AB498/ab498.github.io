<html>
   <head> 
      <meta name="viewport" content="width=device-width, initial-scale=1"> 
      <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.0/Chart.min.js"></script> 
      <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/chartjs-plugin-annotation/0.5.5/chartjs-plugin-annotation.min.js"></script>
   </head> 
   <body> 
      <canvas id="ctx"></canvas>  
      
      <p id="debug">Debug</p>
      
      
      <script type="text/javascript">
      
      
      prc=0;
      lastPrc=0;
      
      //=document.querySelector;
      debug=document.querySelector("#debug");
      d=function(v){debug.textContent=v};
      
chart = new Chart(ctx, {
   type: 'line',
   data: {
      labels: [],
      datasets: [{
        data:[],
        backgroundColor: "#00000000",
        borderColor: "red",
        pointBackgroundColor: 'red',
        pointRadius: 0,
        
      }]
   },
   options: {
      annotation: {
         drawTime: 'afterDatasetsDraw',
         annotations: []
      }
   }
});
    
    
  function getVertical(val, lab){
    
   return  {
      type: 'line',
      scaleID: 'x-axis-0',
      value: val,
      label: {
         enabled: true,
         content: lab
      }
   }
  }
  
  function pushAnno(val, lab){
    chart.options.annotation.annotations.push(getVertical(val, lab));
    chart.update();
  }

var socket = new WebSocket('wss://btc.data.hxro.io/live');
      
  socket.onmessage = function (event) {
    
    var msg = (event.data);
    dat=JSON.parse(JSON.stringify(msg).replaceAll("\\","").slice(1,-1));
    prc=parseFloat(dat["price"]);
    ts=new Date(dat["ts"]);
    tsNow=ts.getMinutes()+":"+ts.getSeconds();
        col="red";
    col2="blue"

    if(lastPrc-prc<5&&prc-lastPrc<5)addData(chart, 0, tsNow, prc, col);
    //console.log(ts.getSeconds()%10);
    if(ts.getSeconds()==0){
      pushAnno(tsNow, prc);
      
    }
    d(chart.data.labels.length);
    removeExtra();
    
    lastPrc=prc;
  }
  
   function removeExtra(){
     
     if(chart.data.labels.length>100){
          //removeData(chart,0,chart.data.labels.length-100);
          nTh=2;
          var i = Math.floor(chart.data.labels.length / nTh);

while (i--) {
  if(chart.data.labels[(i + 1)*nTh-1].split(":")[1]!=0){
  chart.data.labels.splice((i + 1) * nTh - 1, 1);
    chart.data.datasets.forEach((dataset) => {
    dataset.data.splice((i + 1) * nTh - 1, 1);
    
    //dataset.backgroundColor.splice((i + 1) * nTh - 1, 1);
    });
  }
}
}
     
   }    
  function addData(chart, dsNum, label, data, color, sameLabel) {
    if(!sameLabel)chart.data.labels.push(label);
    chart.data.datasets[dsNum].data.push(data);
    //chart.data.datasets[dsNum].backgroundColor.push(color);
    
    chart.update();
  }
      
      function removeData(chart, start, end) {
    chart.data.labels.splice(start,end);
    chart.data.datasets.forEach((dataset) => {
    dataset.data.splice(start,end);
    dataset.backgroundColor.splice(start,end);
    });
    //chart.update();
    }
      
 
      </script> 
   </body>
</html>