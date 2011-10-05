set(libmusical_lib_src
	CSUUMidiReader/midi2pod2.cpp
	CSUUMidiReader/midi_reader.cpp
	IMACPP/MeterCollection.cpp
	IMACPP/MetroWeights_Mazzola.cpp
	IMACPP/Metrum.cpp
	IMACPP/OnsetGroup_Memory.cpp
	core/AlignmentAlgorithm.cpp
	core/AlignmentVisualizer.cpp
	core/ConstantAffineGapRater.cpp
	core/ConstantLinearGapRater.cpp
	core/Converter.cpp
	core/GapRater.cpp
	core/JSONFileSource.cpp
	core/JSONMysqlSource.cpp
	core/JSONReader.cpp
	core/JSONSource.cpp
	core/miscfunctions.cpp
	core/NeedlemanWunsch.cpp
	core/NeedlemanWunschGotoh.cpp
	core/NWGTrace.cpp
	core/NWTrace.cpp
	core/Reader.cpp
	core/Sequence.cpp
	core/Sequences.cpp
	core/SimilarityRater.cpp
	core/SmithWaterman.cpp
	core/Symbol.cpp
	core/SymbolRegistry.cpp
	core/Trace.cpp
	libjson/Source/internalJSONNode.cpp
	libjson/Source/JSON_Base64.cpp
	libjson/Source/JSONChildren.cpp
	libjson/Source/JSONDebug.cpp
	libjson/Source/JSONIterators.cpp
	libjson/Source/JSONMemory.cpp
	libjson/Source/JSONNode.cpp
	libjson/Source/JSONNode_Mutex.cpp
	libjson/Source/JSONStream.cpp
	libjson/Source/JSONValidator.cpp
	libjson/Source/JSONWorker.cpp
	libjson/Source/JSONWriter.cpp
	libjson/Source/libjson.cpp
	specializations/midi/MidiExactPitchIntervalSimilarityRater.cpp
	specializations/midi/MidiJSONReader.cpp
	specializations/midi/MidiFileReader.cpp
	specializations/midi/MidiSymbol.cpp
	specializations/nlb/ExactPitch40SimilarityRater.cpp
	specializations/nlb/OptiJSONReader.cpp
	specializations/nlb/OptiJSONReader_Registry.cpp
	specializations/nlb/OptiSequence.cpp
	specializations/nlb/OptiSequences.cpp
	specializations/nlb/OptiSimilarityRater.cpp
	specializations/nlb/OptiSimilarityRater_Registry.cpp
	specializations/nlb/OptiSymbol.cpp
)

include_directories(core libjson IMACPP CSUUMidiReader)

add_definitions(-DNDEBUG)

add_library(musical SHARED ${libmusical_lib_src})

install(
	FILES CSUUMidiReader/csuu_midi.h
		CSUUMidiReader/csuu_pod.h
		CSUUMidiReader/file_holder.h
		CSUUMidiReader/pod_rep.h
		IMACPP/MeterCollection.h
		IMACPP/MetroMath.h
		IMACPP/MetroWeights_Mazzola.h
		IMACPP/Metrum.h
		IMACPP/OnsetGroup_Memory.h
		IMACPP/WeightSet.h
		core/AlignmentAlgorithm.cpp
		core/AlignmentAlgorithm.h
		core/AlignmentVisualizer.h
		core/ConstantAffineGapRater.h
		core/ConstantLinearGapRater.h
		core/Converter.h
		core/GapRater.h
		core/JSONFileSource.h
		core/JSONMysqlSource.h
		core/JSONReader.h
		core/JSONSource.h
		core/libmusical.h
		core/miscfunctions.h
		core/NeedlemanWunsch.h
		core/NeedlemanWunschGotoh.h
		core/NWGTrace.h
		core/NWTrace.h
		core/Reader.h
		core/Sequence.h
		core/Sequences.h
		core/SimilarityRater.h
		core/SmithWaterman.h
		core/Symbol.h
		core/SymbolRegistry.h
		core/Trace.h
		specializations/midi/MidiAlignment.h
		specializations/midi/MidiExactPitchIntervalSimilarityRater.h
		specializations/midi/MidiFileReader.h
		specializations/midi/MidiJSONReader.h
		specializations/midi/MidiSymbol.h
		specializations/nlb/ExactPitch40SimilarityRater.h
		specializations/nlb/OptiAlignment.h
		specializations/nlb/OptiJSONReader.h
		specializations/nlb/OptiJSONReader_Registry.h
		specializations/nlb/OptiSequence.h
		specializations/nlb/OptiSequences.h
		specializations/nlb/OptiSimilarityRater.h
		specializations/nlb/OptiSimilarityRater_Registry.h
		specializations/nlb/OptiSymbol.h
	DESTINATION include/libmusical)

install(DIRECTORY libjson/ DESTINATION include/libmusical FILES_MATCHING PATTERN "*.h" PATTERN ".svn" EXCLUDE)

install(TARGETS musical LIBRARY DESTINATION lib)
