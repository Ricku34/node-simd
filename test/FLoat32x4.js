const SIMD = require('bindings')('simd')

var a = SIMD.Float32x4(-5, 2, 0, NaN);
var r = SIMD.Float32x4.abs(a);
console.assert(r[0]==5);
console.assert(r[1]==2);
console.assert(r[2]==0);
console.assert(isNaN(r[3]));
a[0]=-1;a[1]=-2;a[2]=3;a[3]=4;
var b = SIMD.Float32x4(3, 3, 3, 3);
r = SIMD.Float32x4.add(a, b);
console.assert(SIMD.Float32x4.extractLane(r,0)==2);
console.assert(SIMD.Float32x4.extractLane(r,1)==1);
console.assert(SIMD.Float32x4.extractLane(r,2)==6);
console.assert(SIMD.Float32x4.extractLane(r,3)==7);

a = SIMD.Float32x4(2, 2, 2, 2);
b = SIMD.Float32x4(4, 4, 4, 4);
r = SIMD.Float32x4.div(a, b);
for(var i=0;i<4;i++)
    console.assert(SIMD.Float32x4.extractLane(r,i)==0.5);

SIMD.Float32x4.check(a);
["" ,5 , false, [1, 2, 5, 5],].forEach(function (type) {
    var typeError = false;
    try
    {
        SIMD.Float32x4.check(type);
    } catch (e) {
        typeError = e instanceof TypeError;
    }
    console.assert(typeError);
});



