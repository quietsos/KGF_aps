import mqtt from 'mqtt';
import { mongoConn } from './dbConnection';
import { baseStationDataSchema } from './mongodSchema/baseStationSchema';

let mqttConnection = mqtt.connect("mqtt://test.mosquitto.org")



let tag1_baseStation1 = 'tag1_baseStation1'
let tag2_baseStation1 = 'tag2_baseStation1'
let tag3_baseStation1 = 'tag3_baseStation1'
let tag4_baseStation1 = 'tag4_baseStation1'
let tag5_baseStation1 = 'tag5_baseStation1'
let tag6_baseStation1 = 'tag6_baseStation1'


mqttConnection.on("connect", ()=>{
   
    mqttConnection.subscribe(tag1_baseStation1)
    mqttConnection.subscribe(tag2_baseStation1)
    mqttConnection.subscribe(tag3_baseStation1)
    mqttConnection.subscribe(tag4_baseStation1)
    mqttConnection.subscribe(tag5_baseStation1)
    mqttConnection.subscribe(tag6_baseStation1)

    
    console.log("Successfully Subscribed")
})



mqttConnection.on('message', async (topic, message) =>{

    console.log(message.toString())
    let deviceData = message.toString();

    let funRes_MongoDB = await saveDataInMongoDB(JSON.parse(deviceData))
    console.log(funRes_MongoDB)
})


mongoConn()


function saveDataInMongoDB(inputJSON){
    try{
        return new Promise(async(resolve,reject) =>{
            await baseStationDataSchema.insertMany(inputJSON).then((result: any) => {
                if (result.length>0){
                    resolve({statusCode: 100, message: "Saved in MongoDB"})
                }
                else{
                    reject({statusCode: 201, message: "No data to insert"})
                }
            }).catch((e)=>{
                reject({statusCode: 400, message: e.message})
            })
        })
    }catch(e:any){
        console.log(e.message)
    }
}


