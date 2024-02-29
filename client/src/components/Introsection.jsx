import React from "react";
import { useState } from "react";
const cities = [
  "Toronto",
  "Vancouver",
  "Montreal",
  "Calgary",
  "Ottawa",
  "Edmonton",
  "Quebec_City",
  "Mississauga",
  "Winnipeg",
  "Halifax",
  "North_York",
  "Saskatoon",
  "Victorio",
  "Ontario",
  "Alberta",
];
const Introsection = () => {
  const [selectedCity, setSelectedCity] = useState("");

  const handleCityChange = (event) => {
    setSelectedCity(event.target.value);
  };
  return (
    <div className="w-full h-full min-h-[95vh] z-10 flex justify-start pt-32 items-center flex-col bg-black ">
      <p className="text-4xl  p-4 text-white">Select your city of operation</p>
      <select value={selectedCity} onChange={handleCityChange} className="py-[4px] p-4 focus:outline-none min-w-[500px] min-h-[40px] w-full max-w-[160px]  bg-[#ececf3] shadow-inner rounded shadow-outer flex justify-end items-center gap-2 overflow-auto max-h-[400px]">
        <option value="">Select a city</option>
        {cities.map((city) => (
          <option key={city} value={city} className="overflow-auto max-h-[400px]">
            {city}
          </option>
        ))}
      </select>
      {selectedCity && <p className="text-white">You have selected: {selectedCity}</p>}
      {/* <input type="text" className="" /> */}
    </div>
  );
};

export default Introsection;
