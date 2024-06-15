/* can you create a c program that, when invoked, do exactly the same functionality as this one ? */



/* utils.js : */
type isoBuyParams = {
    symbol : string;
    isIsolated : string;
    side : string;
    type : string;
    quantity : number;
    newOrderRespType : string;
    sideEffectType : string;
    timestamp : number;
}
type typeParam = debtParams | isoBuyParams | isoStopParams | cancelOrds | spotBuyParams | spotStopParams;

function generateQueryString(params:typeParam, apiSecret: string): string {
    console.log(params);
    let queryString = Object.entries(params)
        .map(([key, value]) => `${key}=${encodeURIComponent(value)}`)
        .join('&');

    const signature = crypto.createHmac('sha256', apiSecret)
        .update(queryString)
        .digest('hex');

    return `${queryString}&signature=${signature}`;
}

/* isolatedBuy.ts  : */
/* Buy on isolated margin, in borrow mode */
import {generateQueryString} from "../utils/utils";

async function isolatedBuyBor(symbol:string, quantity:number, apiKey:string, apiSecret:string){
    try{
         const timestamp= Date.now();
       const endpoint = "https://api.binance.com/sapi/v1/margin/order";
             const params ={
                                    symbol,
                                    isIsolated : "TRUE",
                                    side : "BUY",
                                    type : "MARKET",/*MARKET*/
                                    /*quoteOrderQty,*/
                                    quantity: quantity,
                                    /*price : 40000,*/
                                    newOrderRespType:"FULL",
                                    sideEffectType : "AUTO_BORROW_REPAY",
                                    /*timeInForce : "GTC", *//* mandatory for limit orders */
                                    timestamp
                            };

                    const queryString = generateQueryString(params, apiSecret);
                    const url = `${endpoint}?${queryString}`;

                    const request = await  fetch(url, {
                                    method:"POST",
                                    headers:{
                                                        "X-MBX-APIKEY": apiKey,
                                                        "Content-Type": "application/x-www-form-urlencoded"
                                                    }
                                })

                    const response = await request.json();
                    return response;

    }catch(error){
             console.log("Error", error)
             throw error;
    }
}


/* Entry.ts */
/* this file calls the function and take the api 
keys from a .env file */

import dotenv from "dotenv";
dotenv.config();
const _apiKey = process.env.BINANCE_API_KEY ?? "";
const _apiSecret = process.env.BINANCE_SECRET ?? "";


async function buy(
	symbol: string,
	quantity: number,
	_apiKey: string,
	_apiSecret: string
): Promise<any> {
	let tx = "";
	tx = await isolatedBuyBor(symbol, quantity, _apiKey, _apiSecret);

	return tx;
}

const tx = buy(
    symbol,
    new_bitcoin,
    _apiKey,
    _apiSecret
);