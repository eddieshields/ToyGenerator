#-- Dynamic libraries from AmpGen
#--- Quick and dirty approach, could do with come cleaning up.
file(GLOB MODELS "models/*.cpp")
foreach(model ${MODELS})
    get_filename_component(MODEL_NAME ${model} NAME_WE)
    execute_process(COMMAND g++ -Ofast -shared -rdynamic --std=c++14 -fPIC -march=native ../models/${MODEL_NAME}.cpp -o ../models/${MODEL_NAME}.so)
    #add_library(${MODEL_NAME} SHARED ${model})
endforeach()