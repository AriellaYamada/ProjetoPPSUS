function calculateVariables(file) {
    var reader = new FileReader();
    reader.readAsText(file);
    reader.onload = function(event){
        var csv = event.target.result;

        var data = $.csv.toObjects(csv);

        for (var cur in data) {
            
        }
    }

}