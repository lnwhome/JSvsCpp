
function ackermann(m, n)
{
 return m === 0 ? n + 1 : ackermann(m - 1, n === 0  ? 1 : ackermann(m, n - 1));
}

function main()
{
    const arraySize = 50 * 1000000;
    var array = [];


    var t0 = (new Date).getTime();

    for (let i = 0;i < arraySize; ++i)
    {
        array.push(Math.random());
    }
    console.log("array size " + array.length)

    var t1 = (new Date).getTime();

    console.log("mean value " + array.reduce((a,b) => a + b, 0) / array.length);

    var t2 = (new Date).getTime();

    console.log("ackerman value " + ackermann(4,1))
    
    var t3 = (new Date).getTime();

    console.log("array generation time    " + (t1 - t0) + "ms");
    console.log("mean calculation time    " + (t2 - t1) + "ms");
    console.log("ackermann execution time " + (t3 - t2) + "ms");
}

main();
/*
node --stack_size=10000 js.js
cp js.js /var/www/html/jsvscpp/
*/
