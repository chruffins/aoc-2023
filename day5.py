# any imports?
from math import log10 as log

def log10(x):
    return x > 0 and log(x) or 0

def fill_map(fp, mapper: dict[range, range]):
    fp.readline()
    fp.readline()
    result = fp.readline()
    while result != '\n':
        if (len(result.split())) == 0:
            print("this must be eof...")
            break
        new, old, length = tuple(map(int, result.split()))
        print(new, old, length)

        mapper.update({range(old, old + length): range(new, new + length)})
        result = fp.readline()

def fill_container(old_list: list[int], new_list: list[int], mapper: dict[range, range]):
    for old in old_list:
        filled = False
        for key, value in mapper.items():
            if old in key:
                # print(f"{log10(old):.3f} in {log10(key.start):.3f}-{log10(key.stop):.3f} -> {log10(old - key.start + value.start):.3f} in {log10(value.start):.3f}-{log10(value.stop):.3f}")
                assert old - key.start + value.start in value, "what...?"
                new_list.append(old - key.start + value.start)
                filled = True
                break
        if not filled:
            # print(f"{log10(old):.3f} NOT in any ranges")
            new_list.append(old)
    
    assert len(old_list) == len(new_list), f"what the fuck? {len(old_list)} {len(new_list)}"

def map_tup(old: tuple[int], mapper: dict[range, range]) -> tuple[int]:
    def get_new(elem: int):
        for key, value in mapper.items():
            if elem in key:
                assert elem - key.start + value.start in value, "what...?"
                return value.start + (elem - key.start)
        return elem
    
    return (get_new(elem) for elem in old)

if __name__ == "__main__":
    fp = open("day5.txt")
    seeds: tuple[int] = tuple(map(int, fp.readline().split()[1:]))
    soils: tuple[int]
    ferts: tuple[int]
    waters: tuple[int]
    lights: tuple[int]
    temps: tuple[int]
    hums: tuple[int]
    locations: tuple[int]

    seed_soil: dict[range, range] = dict()
    soil_ferts: dict[range, range] = dict()
    ferts_water: dict[range, range] = dict()
    water_light: dict[range, range] = dict()
    light_temp: dict[range, range] = dict()
    temp_hums: dict[range, range] = dict()
    hums_locations: dict[range, range] = dict()
    maps = [seed_soil, soil_ferts, ferts_water, water_light, light_temp, temp_hums, hums_locations]

    print("processing seed_soil now")
    fill_map(fp, seed_soil)

    print("processing soil_ferts now")
    fill_map(fp, soil_ferts)

    print("processing ferts_water now")
    fill_map(fp, ferts_water)

    print("processing water_light now")
    fill_map(fp, water_light)

    print("processing light_temp now")
    fill_map(fp, light_temp)
    
    print("processing temp_hums now")
    fill_map(fp, temp_hums)

    print("processing hums_locations now")
    fill_map(fp, hums_locations)

    for mapper in maps:
        seeds = map_tup(seeds, mapper)

    """
    fill_container(seeds, soils, seed_soil)
    fill_container(soils, ferts, soil_ferts)
    fill_container(ferts, waters, ferts_water)
    fill_container(waters, lights, water_light)
    fill_container(lights, temps, light_temp)
    fill_container(temps, hums, temp_hums)
    fill_container(hums, locations, hums_locations)
    """

    #print(locations)

    print(min(seeds))

    """
    result = fp.readline()
    while result != '\n':
        soil_start, seed_start, length = tuple(map(int, result.split()))
        seed_soil_map.update({range(seed_start, seed_start + length): range(soil_start, soil_start + length)})
        result = fp.readline()
    """
    """
    for seed in seeds:
        for key, value in seed_soil.items():
            if seed in key:
                soils.append(seed - key.start + value.start)
                break
    """
    # mapped soils now

    fp.readline()
    fp.readline()
    